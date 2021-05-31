// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

#include "NetworkSystem.h"

#include "GameManagerSystem.h"
#include "CollisionSystem.h"
#include "RenderSystem.h"

#include "FightersSystem.h"
#include "BulletsSystem.h"

Game::Game() {
	mngr_.reset(new Manager());
	networkSys_ = nullptr;
	bulletsSys_ = nullptr;
	fightersSys_ = nullptr;
	collisionsSys_ = nullptr;
	gameMngrSys_ = nullptr;
	renderSys_ = nullptr;
}

Game::~Game() {
}

void Game::init(const char *host, Uint16 port) {

	// ask the player for a name
	std::string playerName;
	std::cout << "Enter you name: ";
	std::cin >> playerName;

	SDLUtils::init("Fighters Fight!", 800, 600,
			"resources/config/fighters.resources.json");

	networkSys_ = mngr_->addSystem<NetworkSystem>(host, port, playerName);
	bulletsSys_ = mngr_->addSystem<BulletsSystem>();
	//ballSys_ = mngr_->addSystem<GunSystem>();
	fightersSys_ = mngr_->addSystem<FightersSystem>();
	collisionsSys_ = mngr_->addSystem<CollisionSystem>();
	gameMngrSys_ = mngr_->addSystem<GameManagerSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
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

		bulletsSys_->update();
		fightersSys_->update();
		collisionsSys_->update();
		gameMngrSys_->update();
		networkSys_->update();

		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

