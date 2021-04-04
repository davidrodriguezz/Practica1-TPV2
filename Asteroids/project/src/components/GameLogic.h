// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../sdlutils/ecs/Component.h"
#include "State.h"
#include "AsteroidsManager.h"

class Transform;

class GameLogic: public Component {
public:
	enum Side {
		LEFT = 0, //
		RIGHT
	};

	GameLogic();
	virtual ~GameLogic();

	void init() override;
	void update() override;
private:
	Transform *fighter_;
	State *state_;
	AsteroidsManager *aMngr_;
};

