// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Entity;
class SoundEffect;

class CollisionSystem: public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	void init() override;
	void update() override;
private:
	Entity* leftFighter_;
	Entity* rightFighter_;
	SoundEffect* explosion_;
};

