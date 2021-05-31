#include "FighterSystem.h"
#include "GameManagerSystem.h"
#include "../sdl_network/NetworkSystem.h"
//#include "../components/Health.h"
#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "messages.h"

FighterSystem::FighterSystem() : fighter1_(nullptr), fighter2_(nullptr)
{
}

FighterSystem::~FighterSystem()
{
}

// --- NETWORK ACTIONS --------------------------

void FighterSystem::init()
{
	fighter1_ = createFighter();
	manager_->setHandler<fighter1>(fighter1_);
	fighter2_ = createFighter();
	manager_->setHandler<fighter2>(fighter2_);
}

void FighterSystem::update() 
{
	Uint8 myId = manager_->getSystem<NetworkSystem>()->getId();

	if (myId == 0)
		moveFighter(fighter1_);
	else
		moveFighter(fighter2_);
}

void FighterSystem::moveFighter(Entity* tie)
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;

	Transform* tr_ = GETCMP3(tie, Transform, manager_);
	FighterCtrl* ctrl_ = GETCMP3(tie, FighterCtrl, manager_);
	ShowAtOppositeSide* checkMargins_ = GETCMP3(tie, ShowAtOppositeSide, manager_);
	DeAcceleration* deAcelerate_ = GETCMP3(tie, DeAcceleration, manager_);
	ctrl_->update();
	checkMargins_->update();
	deAcelerate_->update();
	tr_->update();

	manager_->getSystem<NetworkSystem>()->sendFighterPosition(tr_->pos_);
}

void FighterSystem::setFighterPosition(Uint8 id, Vector2D pos)
{
	Entity* e = nullptr;
	if (id == 0) {
		e = fighter1_;
	}
	else {
		e = fighter2_;
	}
	Transform* tr_ = GETCMP3(e, Transform, manager_);
	tr_->pos_ = pos;
}

// --- SYSTEMS COMUNICATION ---------------------------------

//void FighterSystem::receive(const Message& msg)
//{
//	Transform* tr_ = GETCMP3(fighter1_, Transform, manager_);
//	switch (msg.id_) {
//		/*case _FIGHTER_ASTEROID:
//			onCollisionWithAsteroid(msg.col_.b);
//			break;*/
//	case _GAME_OVER:
//		resetFighters();
//		break;
//	case _LOSE_LIFE:
//		tr_->reset();
//		break;
//	default:
//		break;
//	}
//}

// --- CREATE & DELETE -----------------------------

Entity* FighterSystem::createFighter()
{
	Entity* e = manager_->addEntity();;
	//Entity* fighter1_ = manager_->addEntity();
	manager_->addComponent<Transform>(e, Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 20.0f, 20.0f, 0.0f);
	manager_->addComponent<FighterCtrl>(e, GETCMP3(e, Transform, manager_));
	manager_->addComponent<ShowAtOppositeSide>(e, GETCMP3(e, Transform, manager_));
	manager_->addComponent<DeAcceleration>(e, GETCMP3(e, Transform, manager_));
	//manager_->addComponent<Health>(fighter_);
	manager_->addComponent<Image>(e, &sdlutils().images().at("fighter"));
	return e;
}

void FighterSystem::resetFighters()
{
	Transform* tr1_ = GETCMP3(fighter1_, Transform, manager_);
	tr1_->reset();
	Transform* tr2_ = GETCMP3(fighter2_, Transform, manager_);
	tr2_->reset();
	//Health* h_ = GETCMP3(fighter_, Health, manager_);
	//h_->resetLives();
}

//void FighterSystem::onCollisionWithAsteroid(Entity* fighter)
//{
//	Transform* tr_ = GETCMP3(fighter, Transform, manager_);
//	//Health* h_ = GETCMP3(fighter, Health, manager_);
//	/*if (h_->getLives() > 0) {
//		h_->minusLife();
//	}*/
//	tr_->reset();
//
//	sdlutils().soundEffects().at("explosion").play();
//}






