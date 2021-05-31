// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <vector>
#include "../ecs/System.h"

struct Transform;
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
	Entity* initBullet();
	void setBulletInfo(Vector2D pos, Vector2D vel);
private:
	std::vector<Entity*> bullets_;
	SoundEffect *shoot_;
};

