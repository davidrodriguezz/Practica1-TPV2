// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;
typedef unsigned int uint;

class State: public Component {
public:
	enum GameSate {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER, // game over
		GAMEDONE // game complete
	};

	State() :
			score_(0), //
			state_(), //
			maxScore_(3) //
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

	void setScore(int n) {
		score_ = score_ + n;
	}

	GameSate getState() const {
		return state_;
	}

	void setState(GameSate state) {
		state_ = state;
	}

private:
	//void setFighter();
	//std::array<unsigned int, 2> score_;
	uint score_;
	GameSate state_;
	const unsigned int maxScore_;
};

