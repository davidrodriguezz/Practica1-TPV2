// This file is part of the course TPV2@UCM - Samir Genaim

#include "State.h"

#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/ecs/Manager.h"
#include "Transform.h"

void State::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:
				moveBall();
				state_ = RUNNING;
				break;
			case PAUSED:
				moveBall();
				state_ = RUNNING;
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				score_[0] = score_[1] = 0;
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
			std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}

void State::moveBall() {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));

	//FighterTR_->getVel().set(v.normalize() * 2);
}

void State::init() {
	//FighterTR_ = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
	//AsteroidTR_ = entity_->getMngr()->getHandler<Asteroid>()->getComponent<Transform>();
}
