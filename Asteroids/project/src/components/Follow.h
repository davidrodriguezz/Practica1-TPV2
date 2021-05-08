#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/asteroids_macros.h"
#include "Transform.h"

typedef unsigned int uint;

class Follow : public Component {
public:
	Follow(Transform* caza, Transform* tr) :
		Component(),
		objetive_(caza),
		tr_(tr)
	{
		init();
	}
	Follow(Vector2D center, Transform* tr) :
		Component(),
		objetive_(new Transform(center, Vector2D(), 0.0f, 0.0f, 0.0f)),
		tr_(tr)
	{
		init();
	}

	virtual ~Follow() {
	}

	void init() {
		assert(tr_ != nullptr);
		tr_->vel_.set(follow(tr_->pos_, objetive_->pos_));
	}

	void update() {
		Vector2D vel = tr_->vel_;
		float a = angle(vel, tr_->pos_, objetive_->pos_);
		tr_->vel_.set(vel.rotate(a > 0 ? 1.0f : -1.0f));
	}

private:
	Transform* tr_;
	Transform* objetive_;
};