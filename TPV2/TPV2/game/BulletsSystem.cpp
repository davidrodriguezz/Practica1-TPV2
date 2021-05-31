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
		shoot_(nullptr) {
}

BulletsSystem::~BulletsSystem() {
}

void BulletsSystem::init() {
	resetBullets();
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
	/*manager_->getSystem<NetworkSystem>()->sendBulletsInfo(ballTr_->pos_,
			ballTr_->vel_);*/
}

Entity* BulletsSystem::initBullet() {
	Entity* bullet_ = manager_->addEntity();

	// depends on your fighter transform
	Uint8 myId = manager_->getSystem<NetworkSystem>()->getId();

	Entity* e;
	if (myId == 0)
		e = manager_->getHandler<LeftFighter>();
	else
		e = manager_->getHandler<RightFighter>();

	Transform* caza = GETCMP3(e, Transform, manager_);

	Vector2D bPos = caza->pos_ + Vector2D(caza->width_ / 2.0f, caza->height_ / 2.0f) 
		- Vector2D(0.0f, caza->height_ / 2.0f + 5.0f + 12.0f).rotate(caza->rotation_) 
		- Vector2D(2.0f, 10.0f);

	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(caza->rotation_) 
		* (caza->vel_.magnitude() + 5.0f);

	manager_->addComponent<Transform>(bullet_, bPos, bVel, 5.0f, 20.0f, caza->rotation_);
	manager_->addComponent<Image>(bullet_, &sdlutils().images().at("shoot"));
	manager_->addComponent<DisableOnExit>(bullet_, bullet_, manager_);
	manager_->setGroup<Bullets>(bullet_, true);

	manager_->getSystem<NetworkSystem>()->sendBulletInfo(bPos, bVel);

	shoot_ = &sdlutils().soundEffects().at("gun_shot");

	return bullet_;
}

void BulletsSystem::setBulletInfo(Vector2D pos, Vector2D vel) {
	Entity* e = initBullet();
	bullets_.push_back(e);
	Transform* bTr = GETCMP3(e, Transform, manager_);
	bTr->vel_ = vel;
	bTr->pos_ = pos;
}
