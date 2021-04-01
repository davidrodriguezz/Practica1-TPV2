// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameLogic.h"

#include <cassert>
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/ecs/Manager.h"
#include "../utils/Collisions.h"
#include "State.h"
#include "Transform.h"

GameLogic::GameLogic() :
		fighter_(nullptr), //
		state_(nullptr) {

}
GameLogic::~GameLogic() {

}

void GameLogic::init() {
	fighter_ = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
	assert(fighter_ != nullptr);

	state_ = entity_->getComponent<State>();
	assert(state_ != nullptr);
}

void GameLogic::update() {

	if (state_->getState() != State::RUNNING)
		return;

	// check if ball hits paddles
	/*if (Collisions::collides(leftPaddle_->getPos(), leftPaddle_->getW(),
			leftPaddle_->getH(), ball_->getPos(), ball_->getW(), ball_->getH())
			|| Collisions::collides(rightPaddle_->getPos(),
					rightPaddle_->getW(), rightPaddle_->getH(), ball_->getPos(),
					ball_->getW(), ball_->getH())) {

		// change the direction of the ball, and increment the speed
		auto &vel = ball_->getVel(); // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (ball_->getPos().getX() < 0)
		onBallExit(LEFT);
	else if (ball_->getPos().getX() + ball_->getW() > sdlutils().width())
		onBallExit(RIGHT);*/
}

/*void GameLogic::onBallExit(Side side) {

	auto &score_ = state_->getScore();
	auto maxScore_ = state_->getMaxScore();

	assert(state_->getState() == State::RUNNING); // this should be called only when game is runnig

	if (side == LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}

	ball_->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	ball_->getVel().set(0, 0);

	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		state_->setState(State::PAUSED);
	else
		state_->setState(State::GAMEOVER);
}*/
