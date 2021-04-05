#pragma once

#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "Transform.h"

class ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide() :
		tr_(nullptr) {
	}

	virtual ~ShowAtOppositeSide() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (tr_->getPos().getX() + tr_->getW() / 2 < 0) { tr_->setX(sdlutils().width() + tr_->getW() / 2); }
		if (tr_->getPos().getX() - tr_->getW() / 2 > sdlutils().width()) { tr_->setX(tr_->getW() / -2); }
		if (tr_->getPos().getY() + tr_->getH() / 2 < 0) { tr_->setY(sdlutils().height() + tr_->getH() / 2); }
		if (tr_->getPos().getY() - tr_->getH() / 2 > sdlutils().height()) { tr_->setY(tr_->getH() / -2); }
	}

private:
	Transform* tr_;
}
;