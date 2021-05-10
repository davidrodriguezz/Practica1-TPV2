#pragma once
#include <SDL_stdinc.h>
#include <array>

#include "../ecs/System.h"

struct Transform;

class GameCtrlSystem : public System {
public:

	enum GameState : Uint8 {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER, // game over
		GAMEDONE // game completed
	};

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	GameState getState() {
		return state_;
	}

	const auto& getScore() {
		return score_;
	}

	void init() override;
	void update() override;
	void receive(const Message& msg) override;

	void onFighterDeath(); // muere el caza
	void onAsteroidsExtinction(); // se acaban los asteroides
	
private:
	//std::array<unsigned int, 2> score_;
	unsigned int score_;
	GameState state_;
	unsigned int maxScore_;
};
