#include "BulletsSystem.h"

BulletsSystem::BulletsSystem()
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::init()
{
	
}

void BulletsSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;
	// Mueve las balas
	for (auto e : manager_->getEnteties()) {
		pos_ = pos_ + vel_;
	}
	
	// Comprueba si salen de la pantalla
	if (tr_->getPos().getX() + tr_->getW() / 2 < 0
		|| tr_->getPos().getX() - tr_->getW() / 2 > sdlutils().width()
		|| tr_->getPos().getY() + tr_->getH() / 2 < 0
		|| tr_->getPos().getY() - tr_->getH() / 2 > sdlutils().height())
	{
		entity_->setActive(false);
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	createBullet();
	time->reset();
}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	bullet_->setActive(false); // bullet destruction
	//aMngr_->onCollision(static_cast<Asteroid*>(asteroid_)); // asteroid destruction
	state_->setScore(10);

	sdlutils().soundEffects().at("explosion").play();
}

void BulletsSystem::receive(const Message&)
{
}

void BulletsSystem::createBullet() {
	Bullet* b = static_cast<Bullet*>(entity_->getMngr()->addEntity());
	b->init();
}
