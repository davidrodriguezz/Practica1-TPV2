#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"

class Bullet : public Entity
{
public:
	Bullet(Manager* mngr) : Entity(mngr) {};
	~Bullet() { this->setGroup<Bullet_grp>(false); };

	void init() {
		Transform* caza = this->getMngr()->getHandler<Fighter_st>()->getComponent<Transform>();
		sdlutils().soundEffects().at("fire").play();
		Vector2D bPos = caza->pos_ + Vector2D(caza->width_ / 2.0f, caza->height_ / 2.0f) - Vector2D(0.0f, caza->height_ / 2.0f + 5.0f + 12.0f).rotate(caza->getRot()) - Vector2D(2.0f, 10.0f);
		Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(caza->getRot()) * (caza->getVel().magnitude() + 5.0f);
		this->addComponent<Transform>(bPos, bVel, 5.0f, 20.0f, caza->getRot());
		this->addComponent<Image>(&sdlutils().images().at("fire"));
		this->addComponent<DisableOnExit>();
		this->setGroup<Bullet_grp>(true);
	}
};

