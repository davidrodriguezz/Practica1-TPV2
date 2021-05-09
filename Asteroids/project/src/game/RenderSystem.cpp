#include "RenderSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"

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
	if (manager_->getSystem<GameCtrlSystem>()->getState() 
		!= GameCtrlSystem::RUNNING)
		return;

	// render caza: transform + imagen(texture)
	drawIMG(GETCMP3(fighter_, Transform, manager_), GETCMP3(fighter_, Image, manager_));
	// render las balas: son un grupo + igual al caza
	// render de asteroides: igual a las balas
	for (auto& e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e))
			drawFrame(GETCMP3(e, FramedImage, manager_));
	}
	/*for (auto e : manager_->getEntities()) {
		e->render();
	}*/

	// dibujar marcador
	// dibujar mensaje en pause
}

void RenderSystem::drawRect(Transform* tr, SDL_Color color) {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color));

	SDL_Rect rect = build_sdlrect(tr->pos_, tr->width_, tr->height_);

	SDL_RenderFillRect(sdlutils().renderer(), &rect);

}

void RenderSystem::drawIMG(Transform* tr, Image* img)
{
	Vector2D zero = Vector2D();
	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
	SDL_Rect src = build_sdlrect(zero, float(img->tex_->width()), float(img->tex_->height()));
	img->tex_->render(src, dest);
}

void RenderSystem::drawFrame(FramedImage* img)
{
	img->render();
}
