#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/DeAcceleration.h"
#include "../components/Gun.h"
#include "../components/Health.h"

class Fighter : public Entity
{
public:
	Fighter(Manager* mngr) : Entity(mngr) {};
	~Fighter() {};

	void init() {
		this->addComponent<Transform>(
			Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
			Vector2D(), 20.0f, 20.0f, 0.0f);
		this->addComponent<Image>(&sdlutils().images().at("fighter"));
		this->addComponent<FighterCtrl>();
		this->addComponent<ShowAtOppositeSide>();
		this->addComponent<DeAcceleration>();
		this->addComponent<Gun>();
		this->addComponent<Health>();
	}
};

