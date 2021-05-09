#pragma once
#include <SDL_pixels.h>
#include "../ecs/System.h"

#include "../components/Image.h"
#include "../components/FramedImage.h"
class Entity;
struct Transform;

class RenderSystem : public System {
public:
	RenderSystem();
	virtual ~RenderSystem();
	void init() override;
	void update() override;
	void drawRect(Transform* tr, SDL_Color color);
	void drawIMG(Transform* tr, Image* img);
	void drawFrame(FramedImage* img);

private:
	Entity* fighter_;
};
