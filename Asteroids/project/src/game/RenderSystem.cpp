#include "RenderSystem.h"
#include "../sdl_network/NetworkSystem.h"
//#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/FramedImage.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "GameManagerSystem.h"
#include "messages.h"

typedef GameManagerSystem::GameState st;

RenderSystem::RenderSystem() :
	fighter1_(nullptr),
	fighter2_(nullptr),
	pauseLine()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	fighter1_ = manager_->getHandler<fighter1>();
	fighter2_ = manager_->getHandler<fighter2>();
	assert(fighter1_ != nullptr);
	assert(fighter2_ != nullptr);
	pauseLine = "PRESS SPACE TO BEGIN!";
}

void RenderSystem::update()
{
	drawGame();
	/*st state_ = st(manager_->getSystem<GameManagerSystem>()->getState());
	switch (state_) {
	case st::RUNNING:
		drawGame();
		break;
	case st::PAUSED:
	case st::LOSE_LIFE:
	case st::NEWGAME:
	case st::GAMEOVER:
		renderPause();
		break;
	default:
		break;
	}*/
}

// --- SYSTEM COMUNICATION ---------------------------------------

//void RenderSystem::receive(const Message& msg)
//{
//	switch (msg.id_) {
//	case _PAUSE_START:
//		if (msg.c_.data) pauseLine = "TE HAN DISPARADO";
//		else if (!msg.c_.data) pauseLine = "GAME PAUSED";
//		break;
//	case _GAME_OVER:
//		if (msg.c_.data) pauseLine = "CONGRATULATIONS, YOU WIN!!";
//		else if (!msg.c_.data) pauseLine = "GAME OVER";
//		break;
//	default:
//		break;
//	}
//}

// --- UTILS ------------------------------------------------------

void RenderSystem::drawRect(Transform* tr, SDL_Color color) {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color));

	SDL_Rect rect = tr->getRect();

	SDL_RenderFillRect(sdlutils().renderer(), &rect);
}

void RenderSystem::drawIMG(Entity* e_)
{
	Transform*  tr_ = GETCMP3(e_, Transform, manager_);
	Image* img_ = GETCMP3(e_, Image, manager_);
	img_->render(tr_);
}

void RenderSystem::drawFrame(Entity* e_)
{
	FramedImage* img_ = GETCMP3(e_, FramedImage, manager_);
	img_->update();
	img_->render();
}

void RenderSystem::drawText(std::string line, Vector2D pos)
{
	Texture scoreMsg(
		sdlutils().renderer(),
		line,
		sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff)
	);
	SDL_Rect dest = build_sdlrect(pos, float(scoreMsg.width()), float(scoreMsg.height()));
	dest.x = dest.x - scoreMsg.width() / 2;
	scoreMsg.render(dest);
}

// --- GAME -----------------------------------------------------------

void RenderSystem::drawScore()
{
	auto& score_ = manager_->getSystem<GameManagerSystem>()->getScore();
	std::string line = 
		std::to_string(score_[0]) + " - " + std::to_string(score_[1]);
	Vector2D pos = { float(sdlutils().width() / 2), 10.0f };
	drawText(line, pos);
}

void RenderSystem::drawGame()
{
	// render cazas:
	drawIMG(fighter1_);
	drawIMG(fighter2_);
	// render bullets:
	for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			drawIMG(e);
	}
	// render score:
	drawScore();
	drawMsgs();
	drawNames();

	// render de asteroides:
	/*for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e))
			drawFrame(e);
	}*/
	
	// render lifes:
	/*Health* hp_ = GETCMP3(fighter_, Health, manager_);
	hp_->render();*/
}

//void RenderSystem::renderPause()
//{
//	// render score:
//	drawScore();
//	// mensaje:
//	drawPause();
//}
//
//void RenderSystem::drawPause()
//{
//	Vector2D pos = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
//	drawText(pauseLine, pos);
//}

void RenderSystem::drawMsgs() {
	auto state_ = manager_->getSystem<GameManagerSystem>()->getState();
	// message when game is not running
	if (state_ != GameManagerSystem::RUNNING) {

		// game over message
		if (state_ == GameManagerSystem::GAMEOVER) {
			auto& t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() - t.height()) / 2 - 50);
		}

		// new game message
		if (state_ == GameManagerSystem::NEWGAME) {
			auto& t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}
		else {
			auto& t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}

		auto myId = manager_->getSystem<NetworkSystem>()->getId();

		// draw player side message
		Texture side(
			sdlutils().renderer(), //
			(myId == 0 ? "You are playing left" : " You are playing right"),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
		side.render((sdlutils().width() - side.width()) / 2,
			sdlutils().height() - side.height() - 2 * side.height() - 10);

		// draw switch side message
		auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();
		auto isGameReady = manager_->getSystem<NetworkSystem>()->isGameReady();

		if (isMaster && !isGameReady) {
			Texture switch_key(
				sdlutils().renderer(), //
				"(press P to switch side)",
				sdlutils().fonts().at("ARIAL16"),
				build_sdlcolor(0xffffffff));
			switch_key.render((sdlutils().width() - switch_key.width()) / 2,
				sdlutils().height() - switch_key.height() - 10);
		}

	}
}

void RenderSystem::drawNames() {
	auto& names_ = manager_->getSystem<NetworkSystem>()->getNames();

	// name of player 0
	Texture name_0(
		sdlutils().renderer(), //
		names_[0], sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));
	name_0.render(10, 10);

	// name of player 1
	Texture name_1(
		sdlutils().renderer(), //
		names_[1], sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));
	name_1.render(sdlutils().width() - name_1.width() - 10, 10);

	// draw a star next to the master name
	auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();
	auto myId = manager_->getSystem<NetworkSystem>()->getId();

	Texture isMasterMsg(sdlutils().renderer(), //
		"*", //
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xff0000ff));
	isMasterMsg.render(
		(isMaster && myId == 1) || (!isMaster && myId == 0) ?
		sdlutils().width() - isMasterMsg.width() - 1 : 1, 10);

}