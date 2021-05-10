#pragma once

#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide(Transform* tr) :
		tr_(tr) {
	}

	virtual ~ShowAtOppositeSide() {
	}

	void init() {
		assert(tr_ != nullptr);
	}

	void update() {
		if (tr_->pos_.getX() + tr_->width_ / 2 < 0) { tr_->pos_.setX(sdlutils().width() + tr_->width_ / 2); }
		if (tr_->pos_.getX() - tr_->width_ / 2 > sdlutils().width()) { tr_->pos_.setX(tr_->width_ / -2); }
		if (tr_->pos_.getY() + tr_->height_ / 2 < 0) { tr_->pos_.setY(sdlutils().height() + tr_->height_ / 2); }
		if (tr_->pos_.getY() - tr_->height_ / 2 > sdlutils().height()) { tr_->pos_.setY(tr_->height_ / -2); }
	}

private:
	Transform* tr_;
}
;