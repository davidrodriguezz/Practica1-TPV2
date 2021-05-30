#pragma once
#include <SDL_stdinc.h>
#include <array>

#include "../ecs/System.h"

struct Transform;

class GameManagerSystem : public System {
public:

	enum GameState : Uint8 {
		NEWGAME = 0, // just before starting a new game
		PAUSED,	// between rounds
		LOSE_LIFE, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameManagerSystem();
	virtual ~GameManagerSystem();

	Uint8 getState() {
		return state_;
	}

	const auto& getScore() {
		return score_;
	}

	void init() override;
	void update() override;
	void receive(const Message& msg) override;

	void onFighterDeath(); // muere el caza
	//void onAsteroidsExtinction(); // se acaban los asteroides

	void startGame();
	void changeState(Uint8 state, Uint8 left_score, Uint8 right_score);
	void resetGame();
	
private:
	std::array<Uint8, 2> score_;
	Uint8 state_;
	Uint8 maxScore_;
};
