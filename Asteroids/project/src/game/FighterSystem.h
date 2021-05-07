#pragma once
#include "../ecs/System.h"

struct Transform;

class FighterSystem: public System {
public:
	FighterSystem();
	virtual ~FighterSystem();
	void init() override;
	void update() override;

	void onCollisionWithAsteroid(Entity* a);

private:
	Transform* fighter_;
};
