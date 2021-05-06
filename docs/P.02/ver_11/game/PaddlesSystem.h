// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Entity;

class PaddlesSystem: public System {
public:
	PaddlesSystem();
	virtual ~PaddlesSystem();
	void init() override;
	void update() override;
private:
	void movePaddle(Entity *e);

	Entity *leftPaddle_;
	Entity *rightPaddle_;
};

