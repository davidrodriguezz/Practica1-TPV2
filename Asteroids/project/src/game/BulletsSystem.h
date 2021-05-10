#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/VirtualTimer.h"

//struct Transform;
class SoundEffect;

class BulletsSystem : public System {
public:
	BulletsSystem();
	virtual ~BulletsSystem();
	void init() override;
	void update() override;

	void shoot();
	void onCollisionWithAsteroid(Entity* b, Entity* a);
	void receive(const Message&) override;

private:
	size_t numOfAsteroids_;
	VirtualTimer* time;
	SoundEffect* sound = nullptr;

	void createBullet();
	void resetBullets();
};