#include "CollisionSystem.h"
#include "../ecs/Manager.h"
#include "messages.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"

CollisionsSystem::CollisionsSystem()
{
	init();
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
	/*for (Entity* asteroid_ : manager_->getEntities())
	{
		if (manager_->isActive(asteroid_) && manager_->hasGroup<Asteroid_grp>(asteroid_)) {
			Transform* a_ = manager_->getComponent<Transform>(asteroid_);	
			Entity* fighter_ = manager_->getHandler<fighter>();
			Transform* tr_ = manager_->getComponent<Transform>(fighter_);
			if (Collisions::collidesWithRotation(tr_->pos_, tr_->width_, tr_->height_, tr_->rotation_,
				a_->pos_, a_->width_, a_->height_, a_->rotation_)) {

				Message m;
				m.id_ = _FIGHTER_ASTEROID;
				m.col_.a = asteroid_;
				m.col_.b = fighter_;
				manager_->send(m);
			}
		}
	}*/

	
	// check if any fighter is hit by any bullet
	for (Entity* bullet_ : manager_->getEntities())
	{
		if (manager_->isActive(bullet_) && manager_->hasGroup<Bullet_grp>(bullet_)) {
			Transform* b_ = manager_->getComponent<Transform>(bullet_); // bullet
			for (Entity* asteroid_ : manager_->getEntities())
			{
				if (manager_->isActive(bullet_) && manager_->isActive(fighter_) && manager_->hasGroup<Asteroid_grp>(asteroid_)) {
					Transform* a_ = manager_->getComponent<Transform>(fighter_); // asteroid

					if (Collisions::collidesWithRotation(a_->pos_, a_->width_, a_->height_, a_->rotation_,
						b_->pos_, b_->width_, b_->height_, b_->rotation_)) {

						Message m;
						m.id_ = _BULLET_FIGHTER;
						m.col_.a = fighter_;
						m.col_.b = bullet_;
						manager_->send(m);
					}
				}
			}
		}
	}

	// check if any asteroid is hit by any bullet
	//for (Entity* bullet_ : manager_->getEntities())
	//{
	//	if (manager_->isActive(bullet_) && manager_->hasGroup<Bullet_grp>(bullet_)) {
	//		Transform* b_ = manager_->getComponent<Transform>(bullet_); // bullet
	//		for (Entity* asteroid_ : manager_->getEntities())
	//		{
	//			if (manager_->isActive(bullet_) && manager_->isActive(asteroid_) && manager_->hasGroup<Asteroid_grp>(asteroid_)) {
	//				Transform* a_ = manager_->getComponent<Transform>(asteroid_); // asteroid

	//				if (Collisions::collidesWithRotation(a_->pos_, a_->width_, a_->height_, a_->rotation_,
	//					b_->pos_, b_->width_, b_->height_, b_->rotation_)) {

	//					Message m;
	//					m.id_ = _BULLET_ASTEROID;
	//					m.col_.a = asteroid_;
	//					m.col_.b = bullet_;
	//					manager_->send(m);
	//				}
	//			}
	//		}
	//	}
	//}
}

