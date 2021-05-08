#include "FighterSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

FighterSystem::FighterSystem()
{
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::init()
{
	fighter_ = manager_->addEntity();
	manager_->addComponent<Transform>(fighter_, Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 20.0f, 20.0f, 0.0f);
	manager_->addComponent<Image>(fighter_, &sdlutils().images().at("fighter"));
	// falta el health
	manager_->setHandler<fighter>(fighter_);
}

void FighterSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState()
		!= GameCtrlSystem::RUNNING)
		return;

	Transform* tr_ = GETCMP3(fighter_, Transform, manager_);
	float thrust_ = 0.2f;
	float speedlimit_ = 3.0f;

	if (ih().keyDownEvent()) {
		auto& vel = tr_->vel_;
		if (ih().isKeyDown(SDL_SCANCODE_UP) || ih().isKeyDown(SDL_SCANCODE_W)) {
			vel.set(vel + Vector2D(0, -1).rotate(tr_->rotation_) * thrust_);
			sdlutils().soundEffects().at("thrust").play();
			if (vel.magnitude() > speedlimit_)
				vel.set(vel.normalize() * speedlimit_);
			tr_->vel_.set(vel);
		}
		else if (ih().isKeyDown(SDL_SCANCODE_RIGHT) || ih().isKeyDown(SDL_SCANCODE_D)) {
			tr_->rotation_ = tr_->rotation_ + 5.0f;
		}
		else if (ih().isKeyDown(SDL_SCANCODE_LEFT) || ih().isKeyDown(SDL_SCANCODE_A)) {
			tr_->rotation_ = tr_->rotation_ - 5.0f;
		}
		else if (ih().isKeyDown(SDL_SCANCODE_SPACE)) { // disparo
			vel.setY(0.0f);
			vel.setX(0.0f);
			tr_->vel_.set(vel);
		}
		else if (ih().isKeyDown(SDL_SCANCODE_DOWN) || ih().isKeyDown(SDL_SCANCODE_S)) {
			// mensaje a BulletSystem
		}
	}
}

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	//Health* h_ = fighter_->getEntity()->getComponent<Health>();
	//if (h_->getLives() > 0) {
	//	h_->minusLife();
	//	aMngr_->setReset();
	//	fighter_->reset();
	//	state_->setState(State::PAUSED);
	//}
	//else {
	//	aMngr_->setReset(); // asteroides y balas tb se desactivan
	//	fighter_->reset();
	//	fighter_->getEntity()->getComponent<Health>()->resetLives();
	//	state_->setState(State::GAMEOVER);
	//}

	sdlutils().soundEffects().at("explosion").play();
}
