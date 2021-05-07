#pragma once
#include "../ecs/System.h"
#include "../entity/Asteroid.h"
#include "../sdlutils/VirtualTimer.h"

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
	std::size_t numOfAsteroids_;
	VirtualTimer* time;
	//SoundEffect* sound = nullptr;
};
