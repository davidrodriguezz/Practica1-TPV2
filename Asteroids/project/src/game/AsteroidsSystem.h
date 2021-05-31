//#pragma once
//#include "../ecs/System.h"
//#include "../ecs/Entity.h"
//#include "../utils/Vector2D.h"
//
//class SoundEffect;
//class VirtualTimer;
//typedef unsigned int uint;
//
//class AsteroidsSystem: public System {
//public:
//	AsteroidsSystem();
//	virtual ~AsteroidsSystem();
//	void init() override;
//	void update() override;
//
//	void addAsteroids(uint n);
//	void onCollisionWithBullet(Entity* a, Entity* b);
//	void receive(const Message&) override;
//
//private:
//	size_t numOfAsteroids_;
//	VirtualTimer* time;
//	SoundEffect* sound = nullptr;
//
//	void resetAsteroids();
//	Entity* createAsteroid(bool gold);
//	bool rndType();
//	Vector2D rndCenter();
//};
