#include "CollisionSystem.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"

CollisionsSystem::CollisionsSystem()
{
}

CollisionsSystem::~CollisionsSystem()
{
}

void CollisionsSystem::init()
{
}

void CollisionsSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
			return;

	// check if fighter is hit by any asteroid
	for (Entity* asteroid_ : manager_->getEntities())
	{
		if (manager_->isActive(asteroid_) && manager_->hasGroup<Asteroid_grp>(asteroid_)) {
			Transform* a_ = manager_->getComponent<Transform>(asteroid_);
			Transform* fighter_ = manager_->getComponent<Transform>(manager_->getHandler<fighter>());
			if (Collisions::collidesWithRotation(fighter_->pos_, fighter_->width_, fighter_->height_, fighter_->rotation_,
				a_->pos_, a_->width_, a_->height_, a_->rotation_)) {

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
	for (Entity* bullet_ : manager_->getEntities())
	{
		if (manager_->isActive(bullet_) && manager_->hasGroup<Bullet_grp>(bullet_)) {
			Transform* b_ = manager_->getComponent<Transform>(bullet_); // bullet
			for (Entity* asteroid_ : manager_->getEntities())
			{
				if (manager_->isActive(bullet_) && manager_->isActive(asteroid_) && manager_->hasGroup<Asteroid_grp>(asteroid_)) {
					Transform* a_ = manager_->getComponent<Transform>(asteroid_); // asteroid

					if (Collisions::collidesWithRotation(a_->pos_, a_->width_, a_->height_, a_->rotation_,
						b_->pos_, b_->width_, b_->height_, b_->rotation_)) {

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

void CollisionsSystem::receive(const Message&)
{
}
