#pragma once

#include "../sdlutils/ecs/Manager.h"
#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/asteroids_macros.h"
#include "../sdlutils/VirtualTimer.h"
#include "../entity/Asteroid.h"
#include "State.h"

typedef unsigned int uint;

class AsteroidsManager : public Component {
public:
	AsteroidsManager() :
		Component(),
		state_(nullptr),
		initDone(false),
		nAst(0),
		time(nullptr)
	{}

	virtual ~AsteroidsManager() {
	}

	void init() override {
		state_ = entity_->getComponent<State>();
		assert(state_ != nullptr);
		time = new VirtualTimer();
	}

	void update() override {
		if (state_->getState() == State::RUNNING) {
			if (!initDone) { 
				setAsteroids(); 
				initDone = true;
			}
			else if (time->currTime() >= 5000) {
				createAsteroid();
				time->reset();
			}
		}
	}

	Asteroid* createAsteroid() {
		int n = sdlutils().rand().nextInt(1, 100 + 1);
		Asteroid* a = static_cast<Asteroid*>(entity_->getMngr()->addEntity());
		++nAst;
		if (n <= 30)
		{
			a->init(true); // gold
		}
		else {
			a->init(false); // clasic
		}
		return a;
	}

	void deleteAsteroid(Asteroid* a) {
		a->setActive(false);
		--nAst;
	}

	void setAsteroids()
	{
		for (int i = 0; i < 10; i++)
		{
			createAsteroid();
		}
	}

	void onCollision(Asteroid* a) {
		// datos
		Vector2D pos = a->getComponent<Transform>()->getPos();
		Vector2D vel = a->getComponent<Transform>()->getVel();
		float w = a->getComponent<Transform>()->getW();
		float h = a->getComponent<Transform>()->getH();
		int r = sdlutils().rand().nextInt(0, 360 + 1);
		// desactiva y crea 2 asteroides
		deleteAsteroid(a);		
		uint n = a->getComponent<Generations>()->getGen() - 1;
		if (n != 0) {
			// primer asteroide
			Asteroid* a1_ = createAsteroid();
			a1_->getComponent<Generations>()->setGen(n);
			a1_->getComponent<Transform>()->setPos(pos + vel.rotate(float(r)) * 2.0f * w);
			a1_->getComponent<Transform>()->setVel(vel.rotate(float(r)) * 1.1f);
			// segundo asteroide
			r = sdlutils().rand().nextInt(0, 360 + 1);
			Asteroid* a2_ = createAsteroid();
			a2_->getComponent<Generations>()->setGen(n);
			a2_->getComponent<Transform>()->setPos(pos + vel.rotate(float(r)) * 2.0f * w);
			a2_->getComponent<Transform>()->setVel(vel.rotate(float(r)) * 1.1f);
		}
	}

	void desactivateAsteroids() {
		for (Entity* asteroid_ : entity_->getMngr()->getEntities())
		{
			if (asteroid_->isActive() && asteroid_->hasGroup<Asteroid_grp>()) {
				asteroid_->setActive(false);
			}
		}
	}

	int getNumAsteroids() { return nAst; };
	void setReset() { 
		initDone = false; 
		desactivateAsteroids();
		nAst = 0;
	}

private:
	int nAst;
	VirtualTimer* time;
	State* state_;
	bool initDone;
};