#include "GameCtrlSystem.h"


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
				m.id_ = _PAUSE_OVER;
				manager_->send(m);
				break;
			case LOSE_LIFE:
				state_ = RUNNING;
				m.id_ = _ROUND_START;
				manager_->send(m);
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				m.id_ = _NEW_GAME;
				manager_->send(m);
				break;
			default:
				break;
			}
		}
	}
	else if (state_ == RUNNING)
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			state_ = PAUSED;
			Message m;
			m.id_ = _PAUSE_START;
			m.c_.data = false;
			manager_->send(m);
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
	case _ROUND_OVER:
		state_ = PAUSED;
		break;
	default:
		break;
	}
}

void GameCtrlSystem::onFighterDeath()
{
	if (state_ != RUNNING) return;

	Entity* fighter_ = manager_->getHandler<fighter>();
	Transform* tr_ = GETCMP3(fighter_, Transform, manager_);
	Health* h_ = GETCMP3(fighter_, Health, manager_);
	if (h_->getLives() > 0) {
		state_ = LOSE_LIFE;
		Message m;
		m.id_ = _PAUSE_START;
		m.c_.data = true;
		manager_->send(m);
	}
	else {
		state_ = GAMEOVER;
		Message m;
		m.id_ = _ROUND_OVER;
		m.c_.data = false;
		manager_->send(m);
	}
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	assert(state_ == RUNNING);

	score_ = score_ + 10;

	if (score_ >= maxScore_) {
		state_ = GAMEOVER;
		Message m;
		m.id_ = _ROUND_OVER;
		m.c_.data = true;
		manager_->send(m);
	}
}
