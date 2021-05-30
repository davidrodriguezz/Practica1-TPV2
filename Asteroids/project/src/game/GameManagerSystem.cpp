#include "GameManagerSystem.h"
#include "BulletsSystem.h"
#include "../sdl_network/NetworkSystem.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "messages.h"

GameManagerSystem::GameManagerSystem() :
	score_(), //
	state_(NEWGAME), //
	maxScore_(300) {
}

GameManagerSystem::~GameManagerSystem() {
}

// --- SYSTEM FUNCTIONS -------------------------

void GameManagerSystem::init() 
{

}

void GameManagerSystem::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			Message m;
			switch (state_) {
			case LOSE_LIFE:
			case PAUSED:
				state_ = RUNNING;
				m.id_ = _PAUSE_OVER;
				manager_->send(m);
				break;
			case NEWGAME:
			case GAMEOVER:
				state_ = RUNNING;
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

// --- MSG DEFINITIONS -------------------------

void GameManagerSystem::receive(const Message& msg) {
	switch (msg.id_) {
	case _BULLET_FIGHTER:
		onFighterDeath();
		break;
	//case _BULLET_ASTEROID:
		//onAsteroidsExtinction();
		//break;
	case _GAME_OVER:
		state_ = GAMEOVER;
		break;
	case _NEW_GAME:
		score_ = 0;
		break;
	default:
		break;
	}
}

// --- GAME DYNAMICS ------------------------

void GameManagerSystem::onFighterDeath()
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
		Message m2;
		m2.id_ = _LOSE_LIFE;
		manager_->send(m2);
	}
	else {
		state_ = GAMEOVER;
		Message m;
		m.id_ = _GAME_OVER;
		m.c_.data = false;
		manager_->send(m);
	}
}

/*void GameManagerSystem::onAsteroidsExtinction()
{
	if (state_ != RUNNING) return;

	score_ = score_ + 10;

	if (score_ >= maxScore_) {
		state_ = GAMEOVER;
		Message m;
		m.id_ = _GAME_OVER;
		m.c_.data = true;
		manager_->send(m);
	}
}*/

// --- NETWORK ACTIONS ------------------------

void GameManagerSystem::startGame()
{
	if (state_ == RUNNING)
		return;

	if (!manager_->getSystem<NetworkSystem>()->isGameReady())
		return;

	auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();

	if (isMaster) {
		state_ = RUNNING;
		//manager_->getSystem<BulletsSystem>()->initBullet();
		manager_->getSystem<NetworkSystem>()->sendStateChanged(state_,
			score_[0], score_[1]);
	}
	else {
		manager_->getSystem<NetworkSystem>()->sendStartGameRequest();
	}
}

void GameManagerSystem::changeState(Uint8 state, Uint8 left_score, Uint8 right_score)
{
	state_ = state;
	score_[0] = left_score;
	score_[1] = right_score;
}

void GameManagerSystem::resetGame()
{
	state_ = NEWGAME;
	score_[0] = score_[1] = 0;
	manager_->getSystem<BulletsSystem>()->resetBullets();
}
