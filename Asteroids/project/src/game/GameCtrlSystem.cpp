#include "GameCtrlSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
//#include "BallSystem.h"
#include "messages.h"

GameCtrlSystem::GameCtrlSystem() :
	score_(), //
	state_(NEWGAME), //
	maxScore_(3) {
}

GameCtrlSystem::~GameCtrlSystem() {
}

void GameCtrlSystem::init() {

}

void GameCtrlSystem::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			Message m;
			switch (state_) {
			case NEWGAME:
				state_ = RUNNING;
				m.id_ = _ROUND_START;
				manager_->send(m);
				break;
			case PAUSED:
				state_ = RUNNING;
				m.id_ = _ROUND_START;
				manager_->send(m);
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				break;
			default:
				break;
			}
		}
	}
}

void GameCtrlSystem::receive(const Message& msg) {
	switch (msg.id_) {
	//case _BALL_EXIT:
	//	//onBallExit(msg.ballExit_.side_);
	//	break;
	default:
		break;
	}
}

void GameCtrlSystem::onFighterDeath()
{
	//assert(state_ == RUNNING);
	//// falta desactivar las balas
	//Health* h_ = fighter_->getEntity()->getComponent<Health>();
	//if (h_->getLives() > 0) {
	//	h_->minusLife();
	//	aMngr_->setReset();
	//	fighter_->reset();
	//	state_ = PAUSED;
	//}
	//else {
	//	aMngr_->setReset();
	//	fighter_->reset();
	//	fighter_->getEntity()->getComponent<Health>()->resetLives();
	//	state_ = GAMEOVER;
	//}

	//sdlutils().soundEffects().at("explosion").play();
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	assert(state_ == RUNNING);

	// falta desactivar las balas
	//aMngr_->setReset(); //desactiva asteroides
	//fighter_->reset();
	state_ = GAMEDONE;
}
