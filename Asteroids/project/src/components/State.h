// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;

class State: public Component {
public:
	enum GameSate {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	State() :
			score_(), //
			state_(), //
			maxScore_(3), //
			FighterTR_(nullptr)
	{
	}

	virtual ~State() {
	}

	auto& getScore() {
		return score_;
	}

	void init() override;
	void update() override;
	void render() override;

	unsigned int getMaxScore() const {
		return maxScore_;
	}

	GameSate getState() const {
		return state_;
	}

	void setState(GameSate state) {
		state_ = state;
	}

private:
	void createAsteroid(bool isGold);
	void setAsteroids();
	void moveBall();

	std::array<unsigned int, 2> score_;
	GameSate state_;
	const unsigned int maxScore_;
	Transform * FighterTR_;
};

