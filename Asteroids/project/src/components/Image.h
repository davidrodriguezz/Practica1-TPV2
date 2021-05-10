#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"

struct Image : Component {
public:
	Image() :
		tex_(nullptr) {
	}
	Image(Texture* tex) :
		tex_(tex) {
	}

	void render(Transform* tr_) {
		Vector2D zero = Vector2D();
		SDL_Rect dest = tr_->getRect();
		tex_->render(dest, tr_->rotation_);
	}

private:
	Texture* tex_;
};
