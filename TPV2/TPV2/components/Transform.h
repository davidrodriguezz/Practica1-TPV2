// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

struct Transform : Component {
public:
	Transform() :
			pos_(), vel_(), width_(), height_(), rotation_() {
	}

	Transform(Vector2D pos, Vector2D vel, float width, float height,
			float rotation) :
			posInit_(pos),
			pos_(pos), //
			vel_(vel), //
			width_(width), //
			height_(height), //
			rotInit_(rotation),
			rotation_(rotation) {
	}

	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
	float rotation_;

	void update() {
		pos_ = pos_ + vel_;
	}

	SDL_Rect getRect() {
		return build_sdlrect(pos_, width_, height_);
	}

	void reset() {
		std::cout << "reset fighters positions" << std::endl;
		vel_ = Vector2D();
		pos_ = Vector2D(posInit_);
		rotation_ = rotInit_;
	}
private:
	Vector2D posInit_;
	float rotInit_;
};

