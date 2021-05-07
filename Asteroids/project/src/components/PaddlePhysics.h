// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class PaddlePhysics: public Component {
public:
	PaddlePhysics() :
			tr_(nullptr) {
	}
	virtual ~PaddlePhysics() {
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
			vel.setY(0);
		} else if (pos.getY() + height > sdlutils().height()) {
			pos.setY(sdlutils().height() - height);
			vel.setY(0);
		}
	}
private:
	Transform *tr_;

};
