#pragma once
#include "../ecs/System.h"

class CollisionsSystem : public System {
public:
	CollisionsSystem();
	virtual ~CollisionsSystem();
	void init() override;
	void update() override;
};