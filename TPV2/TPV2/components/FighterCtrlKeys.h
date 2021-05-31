// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_scancode.h>

#include "../ecs/Component.h"

struct FighterCtrlKeys: Component {

	FighterCtrlKeys(
		SDL_Scancode forward, 
		SDL_Scancode left, 
		SDL_Scancode right, 
		SDL_Scancode stop
	) :
			forward_(forward), //
			left_(left), //
			right_(right), //
			stop_(right) {
	}

	SDL_Scancode forward_;	// up
	SDL_Scancode left_;		// left
	SDL_Scancode right_;	// right
	SDL_Scancode stop_;		// down
};

