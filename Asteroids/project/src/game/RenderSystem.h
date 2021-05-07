#pragma once
#include "../ecs/System.h"

class RenderSystem : public System {
public:
	RenderSystem();
	virtual ~RenderSystem();
	void init() override;
	void update() override;
};
