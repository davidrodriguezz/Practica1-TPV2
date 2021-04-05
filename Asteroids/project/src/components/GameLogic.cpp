// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameLogic.h"

#include <cassert>
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/ecs/Manager.h"
#include "../utils/Collisions.h"
#include "State.h"
#include "Transform.h"
#include "Health.h"

GameLogic::GameLogic() :
		fighter_(nullptr), //
		state_(nullptr),
		aMngr_(nullptr)
{
}

GameLogic::~GameLogic() {

}

void GameLogic::init() {
	fighter_ = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
	assert(fighter_ != nullptr);

	state_ = entity_->getComponent<State>();
	assert(state_ != nullptr);
	
	aMngr_ = entity_->getComponent<AsteroidsManager>();
	assert(aMngr_ != nullptr);
}

void GameLogic::update() {

	if (state_->getState() != State::RUNNING)
		return;

	// check if fighter is hit by any asteroid
	for (Entity* asteroid_ : entity_->getMngr()->getEntities())
	{
		if (asteroid_->isActive() && asteroid_->hasGroup<Asteroid_grp>()) {
			Transform* a_ = asteroid_->getComponent<Transform>();
			if (Collisions::collidesWithRotation(fighter_->getPos(), fighter_->getW(), fighter_->getH(), fighter_->getRot(),
				a_->getPos(), a_->getW(), a_->getH(), a_->getRot())) {

				Health* h_ = fighter_->getEntity()->getComponent<Health>();
				if (h_->getLives() > 0) {
					h_->minusLife();
					asteroid_->setActive(false); // asteroid destruction
					aMngr_->setReset(false);
					fighter_->reset();
					state_->setState(State::PAUSED);
				}
				else {
					aMngr_->setReset(false);
					fighter_->reset();
					fighter_->getEntity()->getComponent<Health>()->resetLives();
					state_->setState(State::GAMEOVER);
				}

				sdlutils().soundEffects().at("explosion").play();
			}
		}
	}

	// check if any asteroid is hit by any bullet
	for (Entity* asteroid_ : entity_->getMngr()->getEntities())
	{
		if (asteroid_->isActive() && asteroid_->hasGroup<Asteroid_grp>()) {
			Transform* a_ = asteroid_->getComponent<Transform>(); // asteroid
			for (Entity* bullet_ : entity_->getMngr()->getEntities())
			{
				if (bullet_->isActive() && bullet_->hasGroup<Bullet_grp>()) {
					Transform* b_ = bullet_->getComponent<Transform>(); // bullet

					if (Collisions::collidesWithRotation(a_->getPos(), a_->getW(), a_->getH(), a_->getRot(),
						b_->getPos(), b_->getW(), b_->getH(), b_->getRot())) {

						aMngr_->onCollision(static_cast<Asteroid*>(asteroid_)); // asteroid destruction
						state_->setScore(10);
						bullet_->setActive(false); // bullet destruction

						// comprueba el final de la partida
						if (aMngr_->getNumAsteroids() == 0) { 
							aMngr_->setReset(false);
							fighter_->reset();
							state_->setState(State::GAMEDONE);
						}

						sdlutils().soundEffects().at("explosion").play();
					}
				}
			}
		}
	}
}