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
		state_(nullptr)
	{}

	virtual ~AsteroidsManager() {
	}

	void init() override {
		state_ = entity_->getComponent<State>();
		assert(state_ != nullptr);
		time = new VirtualTimer();	
		nAst = 0;
		initDone = false;
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
		uint w = a->getComponent<Transform>()->getW();
		uint h = a->getComponent<Transform>()->getH();
		int r = sdlutils().rand().nextInt(0, 360 + 1);
		// desactiva y crea 2 asteroides
		a->setActive(false);
		uint n = a->getComponent<Generations>()->getGen() - 1;
		if (n != 0) {
			// primer asteroide
			Asteroid* a_ = createAsteroid();
			a_->getComponent<Generations>()->setGen(n);
			a_->getComponent<Transform>()->setPos(pos + vel.rotate(r) * 2.0f * w);
			a_->getComponent<Transform>()->setVel(vel.rotate(r) * 1.1f);
			// segundo asteroide
			r = sdlutils().rand().nextInt(0, 360 + 1);
			a_ = createAsteroid();
			a_->getComponent<Generations>()->setGen(n);
			a_->getComponent<Transform>()->setPos(pos + vel.rotate(r) * 2.0f * w);
			a_->getComponent<Transform>()->setVel(vel.rotate(r) * 1.1f);
		}		
	}

	uint getNumAsteroids() { return nAst; };

private:
	uint nAst;
	VirtualTimer* time;
	State* state_;
	bool initDone;
};