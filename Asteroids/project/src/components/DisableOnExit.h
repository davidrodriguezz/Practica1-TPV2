#pragma once

#include <SDL.h>
#include <cassert>
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "Transform.h"

class DisableOnExit : public Component {
public:
	DisableOnExit() :
		tr_(nullptr) {
	}

	virtual ~DisableOnExit() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if ( tr_->getPos().getX() + tr_->getW() / 2 < 0
			|| tr_->getPos().getX() - tr_->getW() / 2 > sdlutils().width()
			|| tr_->getPos().getY() + tr_->getH() / 2 < 0
			|| tr_->getPos().getY() - tr_->getH() / 2 > sdlutils().height() ) 
		{
			entity_->setActive(false);
		}
	}

private:
	Transform* tr_;
}
;