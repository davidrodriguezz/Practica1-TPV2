#pragma once

#include <SDL.h>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

typedef unsigned int uint;

class Health : public Component {
public:
	Health() :
		Component(),
		tex_(nullptr),
		tr_(nullptr),
		lives_(3) {
	}
	virtual ~Health() {
	}

	int getLives() {
		return lives_;
	}
	void minusLife() {
		--lives_;
	}
	void resetLives() {
		lives_ = 3;
	}

	void init() {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		lives_ = 3;
		tex_ = &sdlutils().images().at("heart");
	}

	void render() {
		Vector2D pos(tr_->width_, tr_->height_); // window position is like one fighter cube
		SDL_Rect dest = build_sdlrect(pos, tr_->width_, tr_->height_);
		for (uint i = 0; i < lives_; i++) {
			tex_->render(dest);

			dest.x = dest.x + int(tr_->width_) + 10;
		}
	}

private:
	Transform* tr_;
	Texture* tex_;
	uint lives_;
}
;