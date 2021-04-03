#pragma once

#include <SDL.h>
#include <cassert>

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/ecs/Entity.h"
#include "Transform.h"
#include "../entity/Bullet.h"

class Gun : public Component {
public:
	Gun() :
		tr_(nullptr) {
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
				createBullet();
			}
		}
	}

	void createBullet() {
		Bullet* b = static_cast<Bullet*>(entity_->getMngr()->addEntity());
		b->init(tr_);
	}

private:
	Transform* tr_;
}
;