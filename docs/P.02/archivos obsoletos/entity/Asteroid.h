#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"

class Asteroid : public Entity
{
public:
	Asteroid(Manager* mngr) : Entity(mngr) {};
	~Asteroid() { this->setGroup<Asteroid_grp>(false); };

	void init(bool isGold) {
		Transform* caza = this->getMngr()->getHandler<Fighter_st>()->getComponent<Transform>();
		float x = float(sdlutils().rand().nextInt(0, sdlutils().width() + 1));
		float y = float(sdlutils().rand().nextInt(0, sdlutils().height() + 1));
		Vector2D pos(x, y);
		this->addComponent<Transform>(pos, Vector2D(), 40.0f, 40.0f, 0.0f);
		this->addComponent<ShowAtOppositeSide>();
		this->addComponent<Generations>();
		if (isGold) {
			this->addComponent<Follow>(caza);
			this->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"));
		}
		else {
			float cx = sdlutils().width() / 2.0f;
			float cy = sdlutils().height() / 2.0f;
			float rx = float(sdlutils().rand().nextInt(-100, 100 + 1));
			float ry = float(sdlutils().rand().nextInt(-100, 100 + 1));
			Vector2D center(cx + rx, cy + ry);
			this->addComponent<Follow>(center);
			this->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));
		}
		this->setGroup<Asteroid_grp>(true);
	}
};

