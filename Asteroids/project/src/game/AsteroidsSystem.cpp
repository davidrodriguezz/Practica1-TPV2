#include "AsteroidsSystem.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

AsteroidsSystem::AsteroidsSystem()
{
}

AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::init()
{
	time = new VirtualTimer();
}

void AsteroidsSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
		return;

	for (auto& e : manager_->getEnteties()) {
		if (manager_->hasGroup<Asteroid_grp>(e)) {
			Follow* mov = GETCMP3(e, Follow, manager_);
			FramedImage* img = GETCMP3(e, FramedImage, manager_);
			mov->update();
			img->update();
		}
	}

	if (time->currTime() >= 5000) {
		createAsteroid(rndType());
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
	//bullet_->setActive(false); // bullet destruction
	//aMngr_->onCollision(static_cast<Asteroid*>(asteroid_)); // asteroid destruction
	//state_->setScore(10);

	//// comprueba el final de la partida
	//if (aMngr_->getNumAsteroids() <= 0) {
	//	// enviar mensaje a GameCtrlSystem
	//}

	sdlutils().soundEffects().at("explosion").play();
}

void AsteroidsSystem::receive(const Message&)
{
	/*switch (msg.id_) {
	case _BALL_EXIT:
		onBallExit(msg.ballExit_.side_);
		break;
	default:
		break;
	}*/
}

void AsteroidsSystem::createAsteroid(bool gold)
{
	Entity* asteroid_ = manager_->addEntity();
	float x = float(sdlutils().rand().nextInt(0, sdlutils().width() + 1));
	float y = float(sdlutils().rand().nextInt(0, sdlutils().height() + 1));
	Vector2D pos(x, y);
	Transform* tr_ = manager_->addComponent<Transform>(asteroid_, pos, Vector2D(), 40.0f, 40.0f, 0.0f);
	if (gold) { 
		manager_->addComponent<FramedImage>(asteroid_, &sdlutils().images().at("asteroid_gold"), tr_); 
		manager_->addComponent<Follow>(asteroid_, manager_->getHandler<fighter>(), tr_);
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
