#include "RenderSystem.h"

#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "GameCtrlSystem.h"
#include "messages.h"

typedef GameCtrlSystem::GameState st;

RenderSystem::RenderSystem() :
	fighter_(nullptr),
	pauseLine()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	fighter_ = manager_->getHandler<fighter>();
	assert(fighter_ != nullptr);
	pauseLine = "PRESS SPACE TO BEGIN!";
}

void RenderSystem::update()
{
	st state_ = manager_->getSystem<GameCtrlSystem>()->getState();
	switch (state_) {
	case st::RUNNING:
		renderGame();
		break;
	case st::PAUSED:
	case st::LOSE_LIFE:
	case st::NEWGAME:
	case st::GAMEOVER:
		renderPause();
		break;
	default:
		break;
	}
}

void RenderSystem::receive(const Message& msg)
{
	switch (msg.id_) {
	case _PAUSE_START:
		if (msg.c_.data) pauseLine = "YOU LOSE 1 LIFE, BE CAREFULL!!";
		else if (!msg.c_.data) pauseLine = "GAME PAUSED";
		break;
	case _GAME_OVER:
		if (msg.c_.data) pauseLine = "CONGRATULATIONS, YOU COMPLETE THE GAME!!";
		else if (!msg.c_.data) pauseLine = "GAME OVER";
		break;
	default:
		break;
	}
}

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

void RenderSystem::drawScore(std::string line)
{
	Vector2D pos = { sdlutils().width() / 2.0f, 10.0f };
	drawText(line, pos);
}

void RenderSystem::renderGame()
{
	// render caza:
	drawIMG(fighter_);
	// render bullets:
	for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			drawIMG(e);
	}
	// render de asteroides:
	for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e))
			drawFrame(e);
	}
	// render score:
	auto& score_ = manager_->getSystem<GameCtrlSystem>()->getScore();
	drawScore(std::to_string(score_));
	// render lifes:
	Health* hp_ = GETCMP3(fighter_, Health, manager_);
	hp_->render();
}

void RenderSystem::renderPause()
{
	// render score:
	auto& score_ = manager_->getSystem<GameCtrlSystem>()->getScore();
	drawScore(std::to_string(score_));
	// mensaje:
	drawPause();
}

void RenderSystem::drawPause()
{
	Vector2D pos = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	drawText(pauseLine, pos);
}
