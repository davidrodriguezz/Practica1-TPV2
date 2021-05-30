#pragma once
#include <SDL_stdinc.h>
#include <SDL_pixels.h>
#include <string>
#include "../components/Transform.h"
#include "../utils/Vector2D.h"
#include "../ecs/System.h"

struct Entity;

class RenderSystem : public System {
public:
	RenderSystem();
	virtual ~RenderSystem();

	void init() override;
	void update() override;
	void receive(const Message& msg) override;

private:
	Entity* fighter_;
	std::string pauseLine;

	void drawGame();
	void renderPause();
	void drawPause();
	void drawScore();

	void drawRect(Transform* tr, SDL_Color color);
	void drawIMG(Entity* e_);
	void drawFrame(Entity* e_);
	void drawText(std::string line, Vector2D pos);
};
