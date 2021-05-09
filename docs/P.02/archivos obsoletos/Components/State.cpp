// This file is part of the course TPV2@UCM - Samir Genaim

#include "State.h"

#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void State::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:
				state_ = RUNNING;
				break;
			case PAUSED:
				state_ = RUNNING;
				break;
			case GAMEOVER:			
				state_ = NEWGAME;
				score_ = 0;
				break;
			case GAMEDONE:
				state_ = NEWGAME;
				break;
			default:
				break;
			}
		}
	}
}

void State::render() {
	// message when game is not running
	if (state_ != RUNNING) {

		// game over message
		if (state_ == GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
		}
		// game complete message
		if (state_ == GAMEDONE) {
			auto& t = sdlutils().msgs().at("complete");
			t.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state_ == NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}

	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(score_),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);
}

void State::init() {
	
}
