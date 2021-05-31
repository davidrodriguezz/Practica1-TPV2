// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <vector>
#include "../ecs/System.h"

struct Entity;
class SoundEffect;
class Vector2D;

class BulletsSystem: public System {
public:
	BulletsSystem();
	virtual ~BulletsSystem();
	void init() override;
	void update() override;

	void resetBullets();
	void setBulletInfo(Vector2D pos, Vector2D vel, float rot);

private:
	Entity* initBullet(Vector2D pos, Vector2D vel, float rot);
	std::vector<Entity*> bullets_;
	SoundEffect *shoot_;
};

