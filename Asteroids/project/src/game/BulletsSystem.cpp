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
	for (auto e : manager_->getEnteties()) {
		DisableOnExit* disOnExit = GETCMP3(e, DisableOnExit, manager_);
		disOnExit->update();
		bPos = bPos+ bVel;
	}
	
	// Comprueba si salen de la pantalla
	if (tr_->getPos().getX() + tr_->getW() / 2 < 0
		|| tr_->getPos().getX() - tr_->getW() / 2 > sdlutils().width()
		|| tr_->getPos().getY() + tr_->getH() / 2 < 0
		|| tr_->getPos().getY() - tr_->getH() / 2 > sdlutils().height())
	{
		bullet_->setActive(false);
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
	Transform* caza = this->getMngr()->getHandler<Fighter_st>()->getComponent<Transform>();
	Vector2D bPos = caza->getPos() + Vector2D(caza->getW() / 2.0f, caza->getH() / 2.0f) - Vector2D(0.0f, caza->getH() / 2.0f + 5.0f + 12.0f).rotate(caza->getRot()) - Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(caza->getRot()) * (caza->getVel().magnitude() + 5.0f);

	Transform* tr_ = manager_->addComponent<Transform>(bullet_, pos, Vector2D(), 40.0f, 40.0f, 0.0f);
	manager_->setGroup<Bullet_grp>(bullet_, true);
}
