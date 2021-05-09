#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

struct Image : Component {
public:
	Image() :
		tex_(nullptr) {
	}
	Image(Texture* tex) :
		tex_(tex) {
	}
	Texture* tex_;
};
