#pragma once
#include "../ecs/System.h"
#include "../sdl_network/network_types.h"
#include "../utils/Vector2D.h"

struct Entity;

class FighterSystem: public System {
public:
	FighterSystem();
	virtual ~FighterSystem();
	void init() override;
	void update() override;

	//void onCollisionWithAsteroid(Entity* a);
	void receive(const Message&) override;
	void setFighterPosition(uint8_nt id, Vector2D pos);

private:
	Entity* fighter1_;
	Entity* fighter2_;

	Entity* createFighter();
	void resetFighters();
	void moveFighter(Entity* tie);
};
