#pragma once

#include <SDL.h>
#include <cassert>

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class Gun : public Component {
public:
	Gun() :
		tr_(nullptr){
	}
	virtual ~Gun() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr_->getVel();
			if (ih().isKeyDown(SDL_SCANCODE_S)) {
				//crear bala
				sdlutils().soundEffects().at("fire").play();
				tr_->setVel(Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (vel.magnitude() + 5.0f));
				tr_->setPos(tr_->getPos()+Vector2D(tr_->getW()/2.0f,tr_->getH()/2.0f)-Vector2D(0.0f, tr_->getH() /2.0f+5.0f+12.0f).rotate(tr_->getRot())-Vector2D(2.0f,10.0f));
			}
		}
	}

private:
	Transform* tr_;

}
;