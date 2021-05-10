#pragma once
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

	void drawRect(Transform* tr, SDL_Color color);
	void drawIMG(Entity* e_);
	void drawFrame(Entity* e_);
	void drawText(std::string line, Vector2D pos);

private:
	Entity* fighter_;
	std::string pauseLine;
	void renderGame();
	void renderPause();
	void drawPause();
	void drawScore(std::string line);
};
