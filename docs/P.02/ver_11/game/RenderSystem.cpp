// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "GameManagerSystem.h"

RenderSystem::RenderSystem() :
		ballTr_(nullptr), //
		leftPaddelTr_(nullptr), //
		rightPaddelTr_(nullptr) {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::init() {
	ballTr_ = manager_->getComponent<Transform>(manager_->getHandler<Ball>());
	assert(ballTr_ != nullptr);
	leftPaddelTr_ = manager_->getComponent<Transform>(
			manager_->getHandler<LeftPaddle>());
	assert(leftPaddelTr_ != nullptr);
	rightPaddelTr_ = manager_->getComponent<Transform>(
			manager_->getHandler<RightPaddle>());
	assert(rightPaddelTr_ != nullptr);
}

void RenderSystem::update() {
	drawRect(ballTr_, build_sdlcolor(0x0000ffff));
	drawRect(leftPaddelTr_, build_sdlcolor(0x00ff00ff));
	drawRect(rightPaddelTr_, build_sdlcolor(0xff0000ff));

	drawScore();
	drawMsgs();
}

void RenderSystem::drawRect(Transform *tr, SDL_Color color) {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color));

	SDL_Rect rect = build_sdlrect(tr->pos_, tr->width_, tr->height_);

	SDL_RenderFillRect(sdlutils().renderer(), &rect);

}

void RenderSystem::drawScore() {

	auto &score_ = manager_->getSystem<GameManagerSystem>()->getScore();
	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);
}

void RenderSystem::drawMsgs() {
	auto state_ = manager_->getSystem<GameManagerSystem>()->getState();
	// message when game is not running
	if (state_ != GameManagerSystem::RUNNING) {

		// game over message
		if (state_ == GameManagerSystem::GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2 - 50);
		}

		// new game message
		if (state_ == GameManagerSystem::NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}
}
