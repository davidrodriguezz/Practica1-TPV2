#include "FighterGunSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

#include "GameManagerSystem.h"

FighterGunSystem::FighterGunSystem() : time(nullptr)
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
			Message m;
			m.id_ = _BULLET_SHOOT;
			manager_->send(m);
			time->reset();
		}
	}
}
