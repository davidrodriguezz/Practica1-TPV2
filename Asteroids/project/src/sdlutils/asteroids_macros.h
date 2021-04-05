#pragma once

#include <SDL.h>
#include <string>
#include "../utils/Vector2D.h"
#include "SDLUtils.h"

inline Vector2D follow(Vector2D& pos, Vector2D& target) {
	float x = target.getX() - pos.getX();
	float y = target.getY() - pos.getY();
	Vector2D v(x, y);
	v = v.normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0f);
	return v;
}

inline float angle(Vector2D& vel, Vector2D& pos, Vector2D& target) {
	float x = target.getX() - pos.getX();
	float y = target.getY() - pos.getY();
	Vector2D v(x, y);
	return vel.angle(v);
}