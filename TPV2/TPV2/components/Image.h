// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

struct Image : Component {
	Image() :
			tex_(nullptr) {
	}
	Image(Texture *tex) :
			tex_(tex) {
	}

	void render(Transform* tr_) {
		assert(tex_ != nullptr);
		SDL_Rect dest = tr_->getRect();
		tex_->render(dest, tr_->rotation_);
	}

	Texture *tex_;
};
