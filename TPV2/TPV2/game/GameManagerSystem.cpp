// This file is part of the course TPV2@UCM - Samir Genaim

#include <ostream>
#include "GameManagerSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

#include "FightersSystem.h"
#include "BulletsSystem.h"

#include "NetworkSystem.h"

GameManagerSystem::GameManagerSystem() :
		score_(), //
		state_(NEWGAME), //
		maxScore_(3) 
{
	std::cout << "Initializing GameManagerSystem..." << std::endl;
}

GameManagerSystem::~GameManagerSystem() {
}

void GameManagerSystem::init() {
	select_ = &sdlutils().soundEffects().at("beat");
	intro_ = &sdlutils().soundEffects().at("imperial_march");
	std::cout << "GameManagerSystem done!" << std::endl;
}

void GameManagerSystem::onFighterDeath(Side side) {
	std::cout << "FIGHTER DEATH!" << std::endl;
	assert(state_ == RUNNING); // this should be called only when game is runnig

	if (side == s::LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}

	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		state_ = PAUSED;
	else {
		state_ = GAMEOVER;
	}

	intro_->haltChannel();

	manager_->getSystem<NetworkSystem>()->sendStateChanged(state_, score_[0],
			score_[1]);

}

void GameManagerSystem::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:	
				startGame();
				break;
			case PAUSED:
				startGame();
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				score_[0] = score_[1] = 0;
				manager_->getSystem<NetworkSystem>()->sendStateChanged(state_,
						score_[0], score_[1]);
				break;
			default:
				break;
			}
		} else if (ih().isKeyDown(SDL_SCANCODE_P)) {
			manager_->getSystem<NetworkSystem>()->switchId(); // ??
			select_->play();
		}
	}
}

void GameManagerSystem::startGame() {
	std::cout << "GameManagerSystem: startGame()" << std::endl;
	if (state_ == RUNNING)
		return;

	if (!manager_->getSystem<NetworkSystem>()->isGameReady())
		return;

	resetGame();

	auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();

	if (isMaster) {
		intro_->play();
		state_ = RUNNING;
		manager_->getSystem<NetworkSystem>()->sendStateChanged(state_,
				score_[0], score_[1]);
	} else {
		manager_->getSystem<NetworkSystem>()->sendStartGameRequest();
	}

	std::cout << "GameManagerSystem: startGame() done!" << std::endl;
}

void GameManagerSystem::changeState(Uint8 state, Uint8 left_score,
		Uint8 right_score) {
	state_ = state;
	score_[0] = left_score;
	score_[1] = right_score;
}

void GameManagerSystem::resetGame() {
	state_ = NEWGAME;
	manager_->getSystem<BulletsSystem>()->resetBullets();
	manager_->getSystem<FightersSystem>()->resetFighters();
}
