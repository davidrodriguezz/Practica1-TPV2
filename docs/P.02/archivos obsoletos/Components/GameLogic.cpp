// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameLogic.h"

#include <cassert>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
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
	fighter_ = entity_->getMngr()->getHandler<Fighter_st>()->getComponent<Transform>();
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
			if (Collisions::collidesWithRotation(fighter_->pos_, fighter_->width_, fighter_->height_, fighter_->getRot(),
				a_->pos_, a_->width_, a_->height_, a_->getRot())) {

				/*Health* h_ = fighter_->getEntity()->getComponent<Health>();
				if (h_->getLives() > 0) {
					h_->minusLife();
					aMngr_->setReset();
					fighter_->reset();
					state_->setState(State::PAUSED);
				}
				else {
					aMngr_->setReset();
					fighter_->reset();
					fighter_->getEntity()->getComponent<Health>()->resetLives();
					state_->setState(State::GAMEOVER);
				}

				sdlutils().soundEffects().at("explosion").play();*/
			}
		}
	}

	// check if any asteroid is hit by any bullet
	for (Entity* bullet_ : entity_->getMngr()->getEntities())
	{
		if (bullet_->isActive() && bullet_->hasGroup<Bullet_grp>()) {
			Transform* b_ = bullet_->getComponent<Transform>(); // bullet
			for (Entity* asteroid_ : entity_->getMngr()->getEntities())
			{
				if (bullet_->isActive() && asteroid_->isActive() && asteroid_->hasGroup<Asteroid_grp>()) {
					Transform* a_ = asteroid_->getComponent<Transform>(); // asteroid

					if (Collisions::collidesWithRotation(a_->pos_, a_->width_, a_->height_, a_->getRot(),
						b_->pos_, b_->width_, b_->height_, b_->getRot())) {

						//bullet_->setActive(false); // bullet destruction
						//aMngr_->onCollision(static_cast<Asteroid*>(asteroid_)); // asteroid destruction
						//state_->setScore(10);						

						//// comprueba el final de la partida
						//if (aMngr_->getNumAsteroids() <= 0) { 
						//	aMngr_->setReset();
						//	fighter_->reset();
						//	state_->setState(State::GAMEDONE);
						//}

						//sdlutils().soundEffects().at("explosion").play();
					}
				}
			}
		}
	}
}