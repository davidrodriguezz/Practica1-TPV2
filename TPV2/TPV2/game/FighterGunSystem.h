#pragma once
#include "../ecs/System.h"
#include "../sdlutils/VirtualTimer.h"

class VirtualTimer;
class BulletsSystem;

class FighterGunSystem : public System {
public:
	FighterGunSystem(BulletsSystem* bSys);
	virtual ~FighterGunSystem();
	void init() override;
	void update() override;

	void createBullet();

private:
	BulletsSystem* bSys_;
	VirtualTimer* time;
};
