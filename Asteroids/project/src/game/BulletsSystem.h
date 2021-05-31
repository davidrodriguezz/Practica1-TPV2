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
	void setBulletInfo(Vector2D pos, Vector2D vel);

private:
	SoundEffect* sound = nullptr;
	Transform *bulletTr_;
	void shoot();

};
