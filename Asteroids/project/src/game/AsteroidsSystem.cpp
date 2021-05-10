#include "AsteroidsSystem.h"
#include "../components/Generations.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/Follow.h"
#include "../ecs/Manager.h"
#include "messages.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/VirtualTimer.h"

AsteroidsSystem::AsteroidsSystem() : numOfAsteroids_(), time(nullptr)
{
}

AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::init()
{
	time = new VirtualTimer();
	addAsteroids(10);
}

void AsteroidsSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
		return;

	for (auto e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e)) {
			Transform* tr_ = GETCMP3(e, Transform, manager_);
			Follow* follow_ = GETCMP3(e, Follow, manager_);
			tr_->update();
			follow_->update();
		}
	}

	if (time->currTime() >= 5000) {
		addAsteroids(1);
		time->reset();
	}
}

void AsteroidsSystem::addAsteroids(int n)
{
	for (size_t i = 0; i < n; i++)
	{
		createAsteroid(rndType());
		++numOfAsteroids_;
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	manager_->setActive(a, false); // asteroid detruction
	--numOfAsteroids_;

	// comprueba el final de la partida
	if (numOfAsteroids_ <= 0) {
		Message m;
		m.id_ = _GAME_COMPLETE;
		manager_->send(m);
	}

	sdlutils().soundEffects().at("explosion").play();
}

void AsteroidsSystem::receive(const Message& msg)
{
	switch (msg.id_) {
	case _BULLET_ASTEROID:
		onCollisionWithBullet(msg.col_.a, msg.col_.b);
		break;
	case _FIGHTER_ASTEROID:
		resetAsteroids();
		break;
	default:
		break;
	}
}

void AsteroidsSystem::resetAsteroids()
{
	for (auto e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e)) {
			manager_->setActive(e, false);
		}
	}
}

void AsteroidsSystem::createAsteroid(bool gold)
{
	Entity* asteroid_ = manager_->addEntity();
	float x = float(sdlutils().rand().nextInt(0, sdlutils().width() + 1));
	float y = float(sdlutils().rand().nextInt(0, sdlutils().height() + 1));
	Vector2D pos(x, y);
	Transform* tr_ = manager_->addComponent<Transform>(asteroid_, pos, Vector2D(), 40.0f, 40.0f, 0.0f);
	manager_->addComponent<ShowAtOppositeSide>(asteroid_, GETCMP3(asteroid_, Transform, manager_));
	manager_->addComponent<Generations>(asteroid_, GETCMP3(asteroid_, Transform, manager_));
	if (gold) { 
		manager_->addComponent<FramedImage>(asteroid_, &sdlutils().images().at("asteroid_gold"), tr_); 
		manager_->addComponent<Follow>(asteroid_, GETCMP3(manager_->getHandler<fighter>(), Transform, manager_), tr_);
	}
	else { 
		manager_->addComponent<FramedImage>(asteroid_, &sdlutils().images().at("asteroid"), tr_); 
		manager_->addComponent<Follow>(asteroid_, rndCenter(), tr_);
	}
	manager_->setGroup<Asteroid_grp>(asteroid_, true);
}

bool AsteroidsSystem::rndType()
{
	int n = sdlutils().rand().nextInt(1, 100 + 1);
	bool gold = false;
	if (n <= 30)
	{
		gold = true; // gold
	}
	else {
		gold = false; // clasic
	}
	return gold;
}

Vector2D AsteroidsSystem::rndCenter()
{
	float cx = sdlutils().width() / 2.0f;
	float cy = sdlutils().height() / 2.0f;
	float r = float(sdlutils().rand().nextInt(0, 100 + 1));
	float a = float(sdlutils().rand().nextInt(-180, 180 + 1));
	Vector2D c = { cx + r, cy };
	c.rotate(a); // comprobar si hace bien la circunferencia
	return c;
}
