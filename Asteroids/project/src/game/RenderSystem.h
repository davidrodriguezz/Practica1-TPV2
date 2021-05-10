#pragma once
#include <SDL_pixels.h>
#include "../ecs/System.h"

class Entity;
struct Transform;

class RenderSystem : public System {
public:
	RenderSystem();
	virtual ~RenderSystem();
	void init() override;
	void update() override;
	void drawRect(Transform* tr, SDL_Color color);
	void drawIMG(Entity* e_);
	void drawFrame(Entity* e_);

private:
	Entity* fighter_;
};
