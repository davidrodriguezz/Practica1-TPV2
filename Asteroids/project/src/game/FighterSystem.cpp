#include "FighterSystem.h"
#include "../entity/Fighter.h"

FighterSystem::FighterSystem()
{
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::init()
{
	Fighter* f = static_cast<Fighter*>(entity_->getMngr()->addEntity());
	f->init();
	mngr_->setHandler<Fighter_st>(caza);
}

void FighterSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;
	pos_ = pos_ + vel_;
}

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	Health* h_ = fighter_->getEntity()->getComponent<Health>();
	if (h_->getLives() > 0) {
		h_->minusLife();
		aMngr_->setReset();
		fighter_->reset();
		state_->setState(State::PAUSED);
	}
	else {
		aMngr_->setReset(); // asteroides y balas tb se desactivan
		fighter_->reset();
		fighter_->getEntity()->getComponent<Health>()->resetLives();
		state_->setState(State::GAMEOVER);
	}

	sdlutils().soundEffects().at("explosion").play();
}
