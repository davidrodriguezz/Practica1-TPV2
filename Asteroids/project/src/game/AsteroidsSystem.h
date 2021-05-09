#pragma once
#include "../ecs/System.h"
#include "../sdlutils/VirtualTimer.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
//struct Transform;
//class SoundEffect;

class AsteroidsSystem: public System {
public:
	AsteroidsSystem();
	virtual ~AsteroidsSystem();
	void init() override;
	void update() override;

	void addAsteroids(int n);
	void onCollisionWithBullet(Entity* a, Entity* b);
	void receive(const Message&) override;

private:
	size_t numOfAsteroids_;
	VirtualTimer* time;
	//SoundEffect* sound = nullptr;

	void createAsteroid(bool gold);
	bool rndType();
	Vector2D rndCenter();
};
