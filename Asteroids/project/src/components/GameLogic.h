// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../sdlutils/ecs/Component.h"
#include "State.h"

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

	void onBallExit(Side);

	Transform *ball_;
	Transform *leftPaddle_;
	Transform *rightPaddle_;
	State *state_;

};

