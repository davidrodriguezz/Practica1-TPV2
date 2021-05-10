#include "FighterSystem.h"
#include "../components/Health.h"
#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "messages.h"

FighterSystem::FighterSystem() : fighter_(nullptr)
{
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::init()
{
	createFighter();
}

void FighterSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
		return;

	Transform* tr_ = GETCMP3(fighter_, Transform, manager_);
	FighterCtrl* ctrl_ = GETCMP3(fighter_, FighterCtrl, manager_);
	ShowAtOppositeSide* checkMargins_ = GETCMP3(fighter_, ShowAtOppositeSide, manager_);
	DeAcceleration* deAcelerate_ = GETCMP3(fighter_, DeAcceleration, manager_);
	ctrl_->update();
	checkMargins_->update();
	deAcelerate_->update();
	tr_->update();
}

void FighterSystem::onCollisionWithAsteroid(Entity* fighter)
{
	Transform* tr_ = GETCMP3(fighter, Transform, manager_);
	Health* h_ = GETCMP3(fighter, Health, manager_);
	if (h_->getLives() > 0) {
		h_->minusLife();
		tr_->reset(); 
	}

	sdlutils().soundEffects().at("explosion").play();
}

void FighterSystem::receive(const Message& msg)
{
	switch (msg.id_) {
	case _FIGHTER_ASTEROID:
		onCollisionWithAsteroid(msg.col_.b);
		break;
	case _NEW_GAME:
		resetFighter();
		break;
	default:
		break;
	}
}

void FighterSystem::createFighter()
{
	fighter_ = manager_->addEntity();
	manager_->addComponent<Transform>(fighter_, Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 20.0f, 20.0f, 0.0f);
	manager_->addComponent<FighterCtrl>(fighter_, GETCMP3(fighter_, Transform, manager_));
	manager_->addComponent<ShowAtOppositeSide>(fighter_, GETCMP3(fighter_, Transform, manager_));
	manager_->addComponent<DeAcceleration>(fighter_, GETCMP3(fighter_, Transform, manager_));
	manager_->addComponent<Health>(fighter_);
	manager_->addComponent<Image>(fighter_, &sdlutils().images().at("fighter"));
	manager_->setHandler<fighter>(fighter_);
}

void FighterSystem::resetFighter()
{
	Transform* tr_ = GETCMP3(fighter_, Transform, manager_);
	Health* h_ = GETCMP3(fighter_, Health, manager_);
	tr_->reset();
	h_->resetLives();
}
