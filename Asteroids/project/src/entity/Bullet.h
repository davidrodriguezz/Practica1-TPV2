#pragma once
#include "../sdlutils/ecs/Entity.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/ecs/Manager.h"

class Bullet : public Entity
{
public:
	Bullet(Manager* mngr) : Entity(mngr) {};
	~Bullet() { this->setGroup<Bullet_grp>(false); };

	void init(Transform* caza) {
		sdlutils().soundEffects().at("fire").play();
		Vector2D bPos = caza->getPos() + Vector2D(caza->getW() / 2.0f, caza->getH() / 2.0f) - Vector2D(0.0f, caza->getH() / 2.0f + 5.0f + 12.0f).rotate(caza->getRot()) - Vector2D(2.0f, 10.0f);
		Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(caza->getRot()) * (caza->getVel().magnitude() + 5.0f);
		this->addComponent<Transform>(bPos, bVel, 5.0f, 20.0f, caza->getRot());
		this->addComponent<Image>(&sdlutils().images().at("fire"));
		this->addComponent<DisableOnExit>();
		this->setGroup<Bullet_grp>(true);
	}
};

