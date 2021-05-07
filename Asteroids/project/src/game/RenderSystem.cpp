#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
}

void RenderSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState()
		!= GameManagerSystem::RUNNING)
		return;

	// render caza: transform + imagen(texture)
	// render las balas: son un grupo + igual al caza
	// render de asteroides: igual a las balas
	for (auto e : manager_->getEnteties()) {
		e->render();
	}

	// dibujar marcador
	// dibujar mensaje en pause
}
