#include "BulletsSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "messages.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/DisableOnExit.h"

BulletsSystem::BulletsSystem()
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::init()
{
	time = new VirtualTimer();
	sound = &sdlutils().soundEffects().at("fire");
}

void BulletsSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
		return;

	// Mueve las balas
	for (auto e : manager_->getEntities()) {
		if (manager_->hasGroup<Bullet_grp>(e)) {
			Transform* tr_ = GETCMP3(e, Transform, manager_);
			DisableOnExit* disOnExit = GETCMP3(e, DisableOnExit, manager_);
			tr_->update();
			disOnExit->update();
		}
	}
}

void BulletsSystem::shoot()
{
	createBullet();
	time->reset();
	sound->play();
}

void BulletsSystem::onCollisionWithAsteroid(Entity* a, Entity* b)
{
	manager_->setActive(b, false); // bullet destruction
}

void BulletsSystem::receive(const Message& msg)
{
	switch (msg.id_) {
	case _BULLET_SHOOT:
		shoot();
		break;
	case _BULLET_ASTEROID:
		onCollisionWithAsteroid(msg.col_.a, msg.col_.b);
		break;
	case _FIGHTER_ASTEROID:
		resetBullets();
		break;
	default:
		break;
	}
}

void BulletsSystem::createBullet() {
	Entity* bullet_ = manager_->addEntity();
	Transform* caza = GETCMP3(manager_->getHandler<fighter>(), Transform, manager_); 
	Vector2D bPos = caza->pos_ + Vector2D(caza->width_ / 2.0f, caza->height_ / 2.0f) - Vector2D(0.0f, caza->height_ / 2.0f + 5.0f + 12.0f).rotate(caza->rotation_) - Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(caza->rotation_) * (caza->vel_.magnitude() + 5.0f);
	manager_->addComponent<Transform>(bullet_, bPos, bVel, 5.0f, 20.0f, caza->rotation_);
	manager_->addComponent<Image>(bullet_, &sdlutils().images().at("fire"));
	manager_->addComponent<DisableOnExit>(bullet_, bullet_, manager_);
	manager_->setGroup<Bullet_grp>(bullet_, true);
}

void BulletsSystem::resetBullets()
{
	for (auto e : manager_->getEntities()) {
		if (manager_->hasGroup<Bullet_grp>(e)) {
			manager_->setActive(e, false);
		}
	}
}
