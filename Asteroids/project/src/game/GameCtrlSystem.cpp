#include "GameCtrlSystem.h"

#include <cassert>
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "messages.h"

GameCtrlSystem::GameCtrlSystem() :
	score_(), //
	state_(NEWGAME), //
	maxScore_(300) {
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
	case _FIGHTER_ASTEROID:
		onFighterDeath();
		break;
	case _BULLET_ASTEROID:
		onAsteroidsExtinction();
		break;
	case _GAME_COMPLETE:
		state_ = GAMEDONE;
		break;
	default:
		break;
	}
}

void GameCtrlSystem::onFighterDeath()
{
	assert(state_ != RUNNING);

	Entity* fighter_ = manager_->getHandler<fighter>();
	Transform* tr_ = GETCMP3(fighter_, Transform, manager_);
	Health* h_ = GETCMP3(fighter_, Health, manager_);
	if (h_->getLives() > 0) {
		state_ = PAUSED;
	}
	else {
		state_ = GAMEOVER;
	}
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	assert(state_ != RUNNING);

	score_ = score_ + 10;

	if (score_ >= maxScore_)
		state_ = GAMEDONE;
}
