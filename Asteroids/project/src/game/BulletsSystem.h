#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

class SoundEffect;

class BulletsSystem : public System {
public:
	BulletsSystem();
	virtual ~BulletsSystem();
	void init() override;
	void update() override;

	void onCollisionWithAsteroid(Entity* b, Entity* a);
	void receive(const Message&) override;
	void createBullet();
	void resetBullets();

private:
	SoundEffect* sound = nullptr;

	void shoot();

};
