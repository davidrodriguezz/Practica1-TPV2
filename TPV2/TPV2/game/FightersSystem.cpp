// This file is part of the course TPV2@UCM - Samir Genaim

#include "FightersSystem.h"

#include "../components/FighterCtrlKeys.h"
#include "../components/Transform.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/DeAcceleration.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "NetworkSystem.h"


FightersSystem::FightersSystem() :
		leftFighter_(nullptr), //
		rightFighter_(nullptr) 
{
	std::cout << "Initializing FightersSystem..." << std::endl;
}

FightersSystem::~FightersSystem() {
}

void FightersSystem::init() {

	leftFighter_ = createFighter(s::LEFT);

	manager_->setHandler<LeftFighter>(leftFighter_);

	rightFighter_ = createFighter(s::RIGHT);
	
	manager_->setHandler<RightFighter>(rightFighter_);

	std::cout << "FightersSystem done!" << std::endl;
}

void FightersSystem::update() {

	// move your fighter only
	Uint8 myId = manager_->getSystem<NetworkSystem>()->getId();

	if (myId == 0)
		moveFighter(leftFighter_);
	else
		moveFighter(rightFighter_);
}

Entity* FightersSystem::createFighter(SideGame side)
{
	std::cout << "CreateFighter begin" << std::endl;

	Entity* fighter = manager_->addEntity();
	Transform* tr;

	std::cout << "basics begins" << std::endl;

	if (side == s::LEFT) {
		std::cout << "LEFT begins" << std::endl;

		tr = manager_->addComponent<Transform>(
			fighter, //
			Vector2D(10.0, sdlutils().height() / 2.0f - 25.0f / 2), //
			Vector2D(), //
			25.0f, 25.0f, 90.0f);

		std::cout << "TRANSFORM finish" << std::endl;

		manager_->addComponent<Image>(fighter, &sdlutils().images().at("left_Fighter"));

		std::cout << "LEFT finish" << std::endl;
	}

	else if (side == s::RIGHT) {
		std::cout << "RIGHT finish" << std::endl;

		tr = manager_->addComponent<Transform>(
			fighter, //
			Vector2D(sdlutils().width() - 10.0f - 25.0f,
				sdlutils().height() / 2.0f - 25.0f / 2), //
			Vector2D(), //
			25.0f, 25.0f, -90.0f);

		manager_->addComponent<Image>(fighter, &sdlutils().images().at("right_Fighter"));

		std::cout << "RIGHT finish" << std::endl;
	}

	std::cout << "basics finish" << std::endl;
	std::cout << "keycodes begins" << std::endl;

	FighterCtrlKeys* keys = manager_->addComponent<FighterCtrlKeys>(fighter, //
		SDL_SCANCODE_UP,
		SDL_SCANCODE_LEFT,
		SDL_SCANCODE_RIGHT,
		SDL_SCANCODE_DOWN
	);

	std::cout << "keycodes finish" << std::endl;

	manager_->addComponent<FighterCtrl>(fighter, tr, keys);
	manager_->addComponent<ShowAtOppositeSide>(fighter, tr);
	manager_->addComponent<DeAcceleration>(fighter, tr);
	
	std::cout << "CreateFighter finish" << std::endl;

	return fighter;
}

void FightersSystem::moveFighter(Entity *e) 
{

	Transform* tr_ = GETCMP3(e, Transform, manager_);
	FighterCtrl* ctrl_ = GETCMP3(e, FighterCtrl, manager_);
	ShowAtOppositeSide* checkMargins_ = GETCMP3(e, ShowAtOppositeSide, manager_);
	DeAcceleration* deAcelerate_ = GETCMP3(e, DeAcceleration, manager_);

	ctrl_->update();
	checkMargins_->update();
	deAcelerate_->update();
	tr_->update();

	manager_->getSystem<NetworkSystem>()->sendFighterPosition(tr_->pos_);

}

void FightersSystem::setFighterPosition(Uint8 id, Vector2D pos) {
	Entity *e = nullptr;
	if (id == 0) {
		e = leftFighter_;
	} else {
		e = rightFighter_;
	}
	auto tr_ = manager_->getComponent<Transform>(e);
	tr_->pos_ = pos;
}

void FightersSystem::resetFighters()
{
	Transform* tr1_ = GETCMP3(leftFighter_, Transform, manager_);
	tr1_->reset();
	Transform* tr2_ = GETCMP3(rightFighter_, Transform, manager_);
	tr2_->reset();
}
