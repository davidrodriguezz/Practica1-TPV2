#pragma once

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/asteroids_macros.h"
#include "Transform.h"

typedef unsigned int uint;

class Follow : public Component {
public:
	Follow(Transform* caza) :
		Component(),
		tr_(nullptr),
		caza_(caza)
	{}
	Follow(Vector2D center) :
		Component(),
		tr_(nullptr),
		caza_(new Transform(center, Vector2D(), 0.0f, 0.0f, 0.0f))
	{}

	virtual ~Follow() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		tr_->setVel(follow(tr_->getPos(), caza_->getPos()));
	}

	void update() override {
		Vector2D vel = tr_->getVel();
		float a = angle(vel, tr_->getPos(), caza_->getPos());
		tr_->setVel(vel.rotate(a > 0 ? 1.0f : -1.0f));
	}

private:
	Transform* tr_;
	Transform* caza_;
};