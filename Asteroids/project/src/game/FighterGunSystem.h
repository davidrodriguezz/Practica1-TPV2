#pragma once
#include "../ecs/System.h"
#include "../sdlutils/VirtualTimer.h"

class VirtualTimer;

class FighterGunSystem : public System {
public:
	FighterGunSystem();
	virtual ~FighterGunSystem();
	void init() override;
	void update() override;
private:
	VirtualTimer* time;
};
