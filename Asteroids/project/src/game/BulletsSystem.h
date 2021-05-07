#pragma once
#include "../ecs/System.h"
#include "../entity/Bullet.h"
#include "../sdlutils/VirtualTimer.h"

//struct Transform;
//class SoundEffect;

class BulletsSystem : public System {
public:
	BulletsSystem();
	virtual ~BulletsSystem();
	void init() override;
	void update() override;

	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void onCollisionWithAsteroid(Entity* b, Entity* a);
	void receive(const Message&) override;

private:
	std::size_t numOfAsteroids_;
	
	//SoundEffect* sound = nullptr;

	void createBullet();
};