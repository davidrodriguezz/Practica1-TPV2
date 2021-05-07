#include "FighterGunSystem.h"

FighterGunSystem::FighterGunSystem()
{
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
	time = new VirtualTimer();
}

void FighterGunSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(SDL_SCANCODE_DOWN) || ih().isKeyDown(SDL_SCANCODE_S) && (time->currTime() >= 250)) {
			// mensaje a BulletSystem de generar bala
		}
	}
}
