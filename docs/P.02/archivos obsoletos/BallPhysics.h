// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class BallPhysics: public Component {
public:
	BallPhysics() :
			tr_(nullptr) {
	}

	virtual ~BallPhysics() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}
	void update() override {
		auto &pos = tr_->getPos();
		auto &vel = tr_->getVel();
		auto height = tr_->getH();

		if (pos.getY() < 0) {
			pos.setY(0);
			vel.setY(-vel.getY());
			sdlutils().soundEffects().at("wall_hit").play();
		} else if (pos.getY() + height > sdlutils().height()) {
			pos.setY(sdlutils().height() - height);
			vel.setY(-vel.getY());
			sdlutils().soundEffects().at("wall_hit").play();
		}

	}

private:
	Transform *tr_;
};

