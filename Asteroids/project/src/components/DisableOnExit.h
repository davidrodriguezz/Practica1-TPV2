#pragma once

#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

class DisableOnExit : public Component {
public:
	DisableOnExit(Entity* e, Manager* mngr) :
		e_(e),
		mngr_(mngr) {
	}

	virtual ~DisableOnExit() {
	}

	void init()
	{
		tr_ = GETCMP3(e_, Transform, mngr_);
		assert(tr_ != nullptr);
	}

	void update() 
	{
		if ( tr_->pos_.getX() + tr_->width_ / 2 < 0
			|| tr_->pos_.getX() - tr_->width_ / 2 > sdlutils().width()
			|| tr_->pos_.getY() + tr_->height_ / 2 < 0
			|| tr_->pos_.getY() - tr_->height_ / 2 > sdlutils().height() ) 
		{
			mngr_->setActive(e_, false); // mensaje?
		}
	}

private:
	Entity* e_;
	Transform* tr_;
	Manager* mngr_;
}
;