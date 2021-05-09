// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/Transform.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../utils/Vector2D.h"

//#include "AsteroidsSystem.h"
//#include "BulletsSystem.h"
#include "FighterSystem.h"
//#include "FighterGunSystem.h"
//#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "RenderSystem.h"

Game::Game() {
	mngr_.reset(new Manager());
	AsteroidsSystem_ = nullptr;
	BulletsSystem_ = nullptr;
	FighterSystem_ = nullptr;
	FighterGunSystem_ = nullptr;
	CollisionSystem_ = nullptr;
	GameCtrlSystem_ = nullptr;
	RenderSystem_ = nullptr;
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Asteroids", 800, 600,
			"resources/config/asteroids.resources.json");

	/*AsteroidsSystem_ = mngr_->addSystem<AsteroidsSystem>();
	BulletsSystem_ = mngr_->addSystem<BulletsSystem>();*/
	FighterSystem_ = mngr_->addSystem<FighterSystem>();
	/*FighterGunSystem_ = mngr_->addSystem<FighterGunSystem>();
	CollisionSystem_ = mngr_->addSystem<CollisionSystem>();*/
	GameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	RenderSystem_ = mngr_->addSystem<RenderSystem>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->refresh();

		/*AsteroidsSystem_->update();
		BulletsSystem_->update();*/
		FighterSystem_->update();
		/*FighterGunSystem_->update();
		CollisionSystem_->update();*/
		GameCtrlSystem_->update();
		
		mngr_->flushMsgsQueue();

		sdlutils().clearRenderer();
		RenderSystem_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}
