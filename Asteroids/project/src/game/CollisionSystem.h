#pragma once
#include "../ecs/System.h"

class Entity;

class CollisionsSystem : public System {
public:
	CollisionsSystem();
	virtual ~CollisionsSystem();
	void init() override;
	void update() override;

private:
	Entity* fighter_;
};