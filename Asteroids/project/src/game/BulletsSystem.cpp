#include "BulletsSystem.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
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
			tr_->pos_ = tr_->pos_ + tr_->vel_;

			DisableOnExit* disOnExit = GETCMP3(e, DisableOnExit, manager_);
			disOnExit->update();
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	createBullet();
	time->reset();
}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	//bullet_->setActive(false); // bullet destruction
	//aMngr_->onCollision(static_cast<Asteroid*>(asteroid_)); // asteroid destruction
	//state_->setScore(10);

	//sdlutils().soundEffects().at("explosion").play();
}

void BulletsSystem::receive(const Message&)
{
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
