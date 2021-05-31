#include "FighterGunSystem.h"

#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"

#include "GameManagerSystem.h"
#include "BulletsSystem.h"
#include "NetworkSystem.h"

FighterGunSystem::FighterGunSystem(BulletsSystem* bSys) : bSys_(bSys), time(nullptr)
{
	std::cout << "Initializing GunSystem..." << std::endl;
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
	time = new VirtualTimer();
	std::cout << "GunSystem done!" << std::endl;
}

void FighterGunSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;

	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(SDL_SCANCODE_DOWN) || ih().isKeyDown(SDL_SCANCODE_S) && (time->currTime() >= 250)) {
			createBullet();
			time->reset();
		}
	}
}

void FighterGunSystem::createBullet()
{
	// depends on your fighter transform
	Uint8 myId = manager_->getSystem<NetworkSystem>()->getId();

	Entity* e;
	if (myId == 0)
		e = manager_->getHandler<LeftFighter>();
	else
		e = manager_->getHandler<RightFighter>();

	Transform* caza = GETCMP3(e, Transform, manager_);

	Vector2D bPos = caza->pos_ + Vector2D(caza->width_ / 2.0f, caza->height_ / 2.0f)
		- Vector2D(0.0f, caza->height_ / 2.0f + 5.0f + 12.0f).rotate(caza->rotation_)
		- Vector2D(2.0f, 10.0f);

	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(caza->rotation_)
		* (caza->vel_.magnitude() + 5.0f);
	
	manager_->getSystem<NetworkSystem>()->sendBulletInfo(bPos, bVel, caza->rotation_);
	bSys_->setBulletInfo(bPos, bVel, caza->rotation_);
}
