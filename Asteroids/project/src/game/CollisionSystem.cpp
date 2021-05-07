#include "CollisionSystem.h"

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
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;

	// check if fighter is hit by any asteroid
	for (Entity* asteroid_ : entity_->getMngr()->getEntities())
	{
		if (asteroid_->isActive() && asteroid_->hasGroup<Asteroid_grp>()) {
			Transform* a_ = asteroid_->getComponent<Transform>();
			if (Collisions::collidesWithRotation(fighter_->getPos(), fighter_->getW(), fighter_->getH(), fighter_->getRot(),
				a_->getPos(), a_->getW(), a_->getH(), a_->getRot())) {

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

					if (Collisions::collidesWithRotation(a_->getPos(), a_->getW(), a_->getH(), a_->getRot(),
						b_->getPos(), b_->getW(), b_->getH(), b_->getRot())) {

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
