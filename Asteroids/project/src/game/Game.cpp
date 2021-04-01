// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/AICtrl.h"
#include "../components/BallPhysics.h"
#include "../components/GameLogic.h"
#include "../components/Image.h"
#include "../components/KeyBoardCtrl.h"
#include "../components/MouseCtrl.h"
#include "../components/PaddlePhysics.h"
#include "../components/Rectangle.h"
#include "../components/State.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/DisableOnExit.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Gun.h"
#include "../components/Health.h"
#include "../sdlutils/ecs/ecs.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/ecs/Manager.h"
#include "../utils/Vector2D.h"

// Asteroids
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/asteroids.resources.json");

	auto* caza = mngr_->addEntity();
	caza->addComponent<Transform>(
		Vector2D(sdlutils().width(), sdlutils().height()),
		Vector2D(), 20.0f, 20.0f, 0.0f);
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	caza->addComponent<FighterCtrl>();
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<DeAcceleration>();
	caza->addComponent<Gun>();
	mngr_->setHandler<Fighter>(caza);

	auto *gameMngr = mngr_->addEntity();
	gameMngr->addComponent<State>();
	gameMngr->addComponent<GameLogic>();
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

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

