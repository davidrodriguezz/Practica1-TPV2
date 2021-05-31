// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include "../utils/Vector2D.h"

struct Entity;

class FightersSystem: public System {
public:

	FightersSystem();
	virtual ~FightersSystem();
	void init() override;
	void update() override;

	enum class Side {
		LEFT = 0, //
		RIGHT
	};
	using s = Side;

	// used to set the fighter position of the other player
	void setFighterPosition(Uint8 id, Vector2D pos);

	void resetFighters();

private:
	Entity* createFighter(Side side);
	void moveFighter(Entity* tie);

	Entity* leftFighter_;
	Entity* rightFighter_;
};
