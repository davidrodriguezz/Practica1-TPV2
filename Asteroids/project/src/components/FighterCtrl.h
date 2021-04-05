#pragma once

#include <SDL.h>

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl() :
		tr_(nullptr), speedlimit_(3.0f), thrust_(0.2f) {
	}
	virtual ~FighterCtrl() {
	}

	inline void setSpeed(float speed) {
		//speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr_->getVel();
			if (ih().isKeyDown(SDL_SCANCODE_UP) || ih().isKeyDown(SDL_SCANCODE_W)) {
				tr_->setVel(tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * thrust_);
				sdlutils().soundEffects().at("thrust").play();
				if (tr_->getVel().magnitude() > speedlimit_)
					tr_->setVel(tr_->getVel().normalize() * speedlimit_);
					
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT) || ih().isKeyDown(SDL_SCANCODE_D)) {
				tr_->setRot(tr_->getRot() + 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT) || ih().isKeyDown(SDL_SCANCODE_A)) {
				tr_->setRot(tr_->getRot() - 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_SPACE)) { // disparo
				vel.setY(0.0f);
				vel.setX(0.0f);
			}
		}
	}

private:
	Transform* tr_;
	float speedlimit_;
	float thrust_;
}
;