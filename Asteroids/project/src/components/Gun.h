#pragma once

#include <SDL.h>

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "../entity/Bullet.h"
#include "../sdlutils/VirtualTimer.h"

class Gun : public Component {
public:
	Gun() :
		Component(),
		time(nullptr) {};

	virtual ~Gun() {
	}

	void init() override {
		time = new VirtualTimer();	
	}

	void update() override {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDL_SCANCODE_DOWN) || ih().isKeyDown(SDL_SCANCODE_S) && (time->currTime() >= 250)) {
				createBullet();
				time->reset();
			}
		}
	}

	void createBullet() {
		Bullet* b = static_cast<Bullet*>(entity_->getMngr()->addEntity());
		b->init();
	}
private:
	VirtualTimer* time;
}
;