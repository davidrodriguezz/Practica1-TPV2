#include "AsteroidsSystem.h"

AsteroidsSystem::AsteroidsSystem()
{
}

AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::init()
{
	state_ = entity_->getComponent<State>();
	assert(state_ != nullptr);
	time = new VirtualTimer();
}

void AsteroidsSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;
	if (state_->getState() == State::RUNNING) {
		if (!initDone) {
			setAsteroids();
			initDone = true;
		}
		else if (time->currTime() >= 5000) {
			createAsteroid();
			time->reset();
		}
	}
}

void AsteroidsSystem::addAsteroids(int n)
{
	int n = sdlutils().rand().nextInt(1, 100 + 1);
	Asteroid* a = static_cast<Asteroid*>(entity_->getMngr()->addEntity());
	++nAst;
	if (n <= 30)
	{
		a->init(true); // gold
	}
	else {
		a->init(false); // clasic
	}
	return a;
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	bullet_->setActive(false); // bullet destruction
	aMngr_->onCollision(static_cast<Asteroid*>(asteroid_)); // asteroid destruction
	state_->setScore(10);

	// comprueba el final de la partida
	if (aMngr_->getNumAsteroids() <= 0) {
		// enviar mensaje a GameCtrlSystem
	}

	sdlutils().soundEffects().at("explosion").play();
}

void AsteroidsSystem::receive(const Message&)
{
	switch (msg.id_) {
	case _BALL_EXIT:
		onBallExit(msg.ballExit_.side_);
		break;
	default:
		break;
	}
}
