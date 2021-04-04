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
	Gun() {};
	virtual ~Gun() {
	}

	void init() override {

	}

	void update() override {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDL_SCANCODE_S)) {
				createBullet();
			}
		}
	}

	void createBullet() {
		Bullet* b = static_cast<Bullet*>(entity_->getMngr()->addEntity());
		b->init();
	}
}
;