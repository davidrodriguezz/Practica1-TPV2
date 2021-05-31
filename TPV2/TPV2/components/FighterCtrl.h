#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "FighterCtrlKeys.h"

struct FighterCtrl : Component {
public:
	FighterCtrl(Transform* tr, FighterCtrlKeys* keys) :
		tr_(tr), keys_(keys), speedlimit_(3.0f), thrust_(0.2f) {
	}

	virtual ~FighterCtrl() {
	}

	void init() {
		assert(tr_ != nullptr);
	}

	void update(){
		if (ih().keyDownEvent()) {
			auto& vel = tr_->vel_;
			if (ih().isKeyDown(keys_->forward_) || ih().isKeyDown(SDL_SCANCODE_W)) {
				vel.set(vel + Vector2D(0, -1).rotate(tr_->rotation_) * thrust_);
				sdlutils().soundEffects().at("thrust").play();
				if (vel.magnitude() > speedlimit_)
					tr_->vel_.set(vel.normalize() * speedlimit_);
				else { tr_->vel_.set(vel); }
			}
			else if (ih().isKeyDown(keys_->right_) || ih().isKeyDown(SDL_SCANCODE_D)) {
				tr_->rotation_ = tr_->rotation_ + 5.0f;
			}
			else if (ih().isKeyDown(keys_->left_) || ih().isKeyDown(SDL_SCANCODE_A)) {
				tr_->rotation_ = tr_->rotation_ - 5.0f;
			}
			else if (ih().isKeyDown(keys_->stop_) || ih().isKeyDown(SDL_SCANCODE_SPACE)) { // disparo
				vel.setY(0.0f);
				vel.setX(0.0f);
			}
		}
	}

private:
	FighterCtrlKeys* keys_;
	Transform* tr_;
	float speedlimit_;
	float thrust_;
};