#include "FighterCtrl.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void FighterCtrl::init()
{
	assert(tr_ != nullptr);
	//thrustSound_ = &sdlutils().soundEffects().at("thrust");
}

void FighterCtrl::update()
{
	if (ih().keyDownEvent()) 
	{
		//std::cout << "FIGHTER MOVES" << std::endl;
		auto& vel = tr_->vel_;
		if (ih().isKeyDown(keys_->forward_) || ih().isKeyDown(SDL_SCANCODE_W)) {

			vel.set(vel + Vector2D(0, -1).rotate(tr_->rotation_) * thrust_);

			if (vel.magnitude() > speedlimit_)
				tr_->vel_.set(vel.normalize() * speedlimit_);
			else { tr_->vel_.set(vel); }

			//thrustSound_->play(0, 2); ERROR
			//std::cout << "SOUND THRUST" << std::endl;
		}
		else if (ih().isKeyDown(keys_->right_) || ih().isKeyDown(SDL_SCANCODE_D)) {
			tr_->rotation_ = tr_->rotation_ + 5.0f;
		}
		else if (ih().isKeyDown(keys_->left_) || ih().isKeyDown(SDL_SCANCODE_A)) {
			tr_->rotation_ = tr_->rotation_ - 5.0f;
		}
		else if (ih().isKeyDown(keys_->stop_)) { // detenerse
			vel.setY(0.0f);
			vel.setX(0.0f);
		}
		//std::cout << "END MOVE" << std::endl;
	}
}
