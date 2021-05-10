#include "RenderSystem.h"

#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "GameCtrlSystem.h"
#include "messages.h"

RenderSystem::RenderSystem() :
	fighter_(nullptr)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	fighter_ = manager_->getHandler<fighter>();
	assert(fighter_ != nullptr);
}

void RenderSystem::update()
{
	/*if (manager_->getSystem<GameCtrlSystem>()->getState() 
		!= GameCtrlSystem::RUNNING)
		return;*/

	// render caza: transform + imagen(texture)
	drawIMG(fighter_);
	// render las balas: son un grupo + igual al caza
	for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			drawIMG(e);
	}
	// render de asteroides: igual a las balas
	for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e))
			drawFrame(e);
	}
	/*for (auto e : manager_->getEntities()) {
		e->render();
	}*/

	// dibujar marcador
	auto& score_ = manager_->getSystem<GameCtrlSystem>()->getScore();
	// score
	Texture scoreMsg(
		sdlutils().renderer(), //
		std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);
	//dibujar vidas
	Health* hp_ = GETCMP3(fighter_, Health, manager_);
	hp_->render();
	// dibujar mensaje en pause
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
