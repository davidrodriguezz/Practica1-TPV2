#pragma once

#include <SDL.h>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl(Transform* tr) :
		tr_(tr), speedlimit_(3.0f), thrust_(0.2f) {
	}

	virtual ~FighterCtrl() {
	}

	void init() {
		assert(tr_ != nullptr);
	}

	void update(){
		if (ih().keyDownEvent()) {
			auto& vel = tr_->vel_;
			if (ih().isKeyDown(SDL_SCANCODE_UP) || ih().isKeyDown(SDL_SCANCODE_W)) {
				vel.set(vel + Vector2D(0, -1).rotate(tr_->rotation_) * thrust_);
				sdlutils().soundEffects().at("thrust").play();
				if (vel.magnitude() > speedlimit_)
					tr_->vel_.set(vel.normalize() * speedlimit_);
				else { tr_->vel_.set(vel); }
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
			}
		}
	}

private:
	Transform* tr_;
	float speedlimit_;
	float thrust_;
};