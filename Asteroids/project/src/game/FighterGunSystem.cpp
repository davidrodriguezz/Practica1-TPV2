#include "FighterGunSystem.h"
#include "../sdlutils/InputHandler.h"
#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "messages.h"

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
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
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
