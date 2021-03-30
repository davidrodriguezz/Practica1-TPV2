// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

class MouseCtrl: public Component {
public:
	MouseCtrl() :
			tr_(nullptr) {
	}

	virtual ~MouseCtrl() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().mouseMotionEvent()) {
			auto &pos = tr_->getPos();
			pos.setY(float(ih().getMousePos().second));
		}
	}
private:
	Transform *tr_;
};
