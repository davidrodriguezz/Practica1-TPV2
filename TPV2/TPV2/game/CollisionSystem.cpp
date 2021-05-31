// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionSystem.h"

#include <cassert>
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameManagerSystem.h"

#include "NetworkSystem.h"

CollisionSystem::CollisionSystem() :
		leftFighter_(nullptr), //
		rightFighter_(nullptr), //
		explosion_(nullptr) 
{
	std::cout << "Initializing CollisionSystem..." << std::endl;
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::init() {
	explosion_ = &sdlutils().soundEffects().at("explosion");
	leftFighter_ = manager_->getHandler<LeftFighter>();
	assert(leftFighter_ != nullptr);
	rightFighter_ = manager_->getHandler<RightFighter>();
	assert(rightFighter_ != nullptr);

	std::cout << "CollisionSystem done!" << std::endl;
}

void CollisionSystem::update() {

	if (!manager_->getSystem<NetworkSystem>()->isMaster())
		return;

	if (manager_->getSystem<GameManagerSystem>()->getState()
			!= GameManagerSystem::RUNNING)
		return;

	Transform* leftFighterTr_ = GETCMP3(leftFighter_, Transform, manager_);
	Transform* rightFighterTr_ = GETCMP3(rightFighter_, Transform, manager_);

	// check if any fighter is hit by any bullet
	for (Entity* bullet_ : manager_->getEnteties())
	{
		if (manager_->isActive(bullet_) && manager_->hasGroup<Bullets>(bullet_))
		{
			Transform* b_ = manager_->getComponent<Transform>(bullet_); // bullet

			if (Collisions::collidesWithRotation(leftFighterTr_->pos_, leftFighterTr_->width_, leftFighterTr_->height_, leftFighterTr_->rotation_,
				b_->pos_, b_->width_, b_->height_, b_->rotation_)) {

				manager_->getSystem<GameManagerSystem>()->onFighterDeath(GameManagerSystem::s::LEFT);

				explosion_->play();

			}
			else if (Collisions::collidesWithRotation(rightFighterTr_->pos_, rightFighterTr_->width_, rightFighterTr_->height_, rightFighterTr_->rotation_,
				b_->pos_, b_->width_, b_->height_, b_->rotation_)) {

				manager_->getSystem<GameManagerSystem>()->onFighterDeath(GameManagerSystem::s::RIGHT);

				explosion_->play();

			}

		}	// end if active bullet
	}	// end for

}
