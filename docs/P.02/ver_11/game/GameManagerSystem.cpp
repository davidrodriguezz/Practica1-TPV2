// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameManagerSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "BallSystem.h"
#include "messages.h"

GameManagerSystem::GameManagerSystem() :
		score_(), //
		state_(NEWGAME), //
		maxScore_(3), //
		ballTr_(nullptr) {
}

GameManagerSystem::~GameManagerSystem() {
}

void GameManagerSystem::init() {
	ballTr_ = manager_->getComponent<Transform>(manager_->getHandler<Ball>());
	assert(ballTr_ != nullptr);
}

void GameManagerSystem::onBallExit(Side side) {

	assert(state_ == RUNNING); // this should be called only when game is runnig

	if (side == LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}

	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		state_ = PAUSED;
	else
		state_ = GAMEOVER;
}

void GameManagerSystem::update() {
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

void GameManagerSystem::receive(const Message &msg) {
	switch (msg.id_) {
	case _BALL_EXIT:
		onBallExit(msg.ballExit_.side_);
		break;
	default:
		break;
	}
}
