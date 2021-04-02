#pragma once

#include <SDL.h>
#include <cassert>

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"


class Health : public Component {
public:
	Health() :
		tr_(nullptr), lives_(3), tex_(&sdlutils().images().at("heart")), src_({ 0, 0, tex_->width(), tex_->height() }) {
	}
	virtual ~Health() {
	}

	int getLives() {
		return lives_;
	}
	void minusLife(int lives) {
		lives_ = lives - 1;
	}
	void resetLives() {
		lives_ = 3;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		Vector2D pos(tr_->getW(), tr_->getH());
		SDL_Rect dest = build_sdlrect(pos, tr_->getW(), tr_->getH());
		for (int i = 0; i < lives_; i++) {
			tex_->render(src_, dest, 0);

			dest.x = dest.x + tr_->getW() + 10;
		}
	}

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
	int lives_;
	float thrust_;
}
;