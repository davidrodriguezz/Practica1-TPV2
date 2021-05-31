// This file is part of the course TPV2@UCM - Samir Genaim

#include "BulletsSystem.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

#include "NetworkSystem.h"

BulletsSystem::BulletsSystem() :
		bullets_(), //
		shoot_(nullptr) 
{
	std::cout << "Initializing BulletsSystem..." << std::endl;
}

BulletsSystem::~BulletsSystem() {
}

void BulletsSystem::init() {
	shoot_ = &sdlutils().soundEffects().at("gun_shot");
	resetBullets();

	std::cout << "BulletsSystem done!" << std::endl;
}

void BulletsSystem::update() {
	for (auto e : bullets_) {
		if (manager_->hasGroup<Bullets>(e)) {
			Transform* bTr = GETCMP3(e, Transform, manager_);
			bTr->update();
		}
	}
}

void BulletsSystem::resetBullets() {
	for (auto e : bullets_) {
		if (manager_->hasGroup<Bullets>(e)) {
			manager_->setActive(e, false);
		}
	}
}

Entity* BulletsSystem::initBullet(Vector2D pos, Vector2D vel, float rot) {
	Entity* bullet_ = manager_->addEntity();
	bullets_.push_back(bullet_);

	manager_->addComponent<Transform>(bullet_, pos, vel, 5.0f, 20.0f, rot);
	manager_->addComponent<Image>(bullet_, &sdlutils().images().at("shoot"));
	manager_->addComponent<DisableOnExit>(bullet_, bullet_, manager_);
	manager_->setGroup<Bullets>(bullet_, true);

	shoot_->play();

	return bullet_;
}

void BulletsSystem::setBulletInfo(Vector2D pos, Vector2D vel, float rot) 
{
	Entity* e = initBullet(pos, vel, rot);
	Transform* bTr = GETCMP3(e, Transform, manager_);
	bTr->vel_ = vel;
	bTr->pos_ = pos;
}
