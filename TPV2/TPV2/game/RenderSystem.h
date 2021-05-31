// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_pixels.h>

#include "../ecs/System.h"

struct Entity;
struct Transform;

class RenderSystem: public System {
public:
	RenderSystem();
	virtual ~RenderSystem();
	void init() override;
	void update() override;
private:

	void drawIMG(Entity* e);
	void drawBullets();

	void drawRect(Transform *tr, SDL_Color color);
	void drawScore();
	void drawMsgs();
	void drawNames();

	Entity* fighter1_;
	Entity* fighter2_;
};

