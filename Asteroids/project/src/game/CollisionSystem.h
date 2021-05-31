#pragma once
#include "../ecs/System.h"

class CollisionsSystem : public System {
public:
	CollisionsSystem();
	virtual ~CollisionsSystem();
	void init() override;
	void update() override;
private:
	Transform *fighter1Tr_;
	Transform *fighter2Tr_;
};