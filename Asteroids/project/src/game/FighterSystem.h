#pragma once
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include "../utils/Vector2D.h"

struct Entity;

class FighterSystem: public System {
public:
	FighterSystem();
	virtual ~FighterSystem();
	void init() override;
	void update() override;

	//void onCollisionWithAsteroid(Entity* a);
	//void receive(const Message&) override;
	void setFighterPosition(Uint8 id, Vector2D pos);
	void resetFighters();
	void moveFighter(Entity* tie);
	Entity* createFighter();

private:
	Entity* fighter1_;
	Entity* fighter2_;

};
