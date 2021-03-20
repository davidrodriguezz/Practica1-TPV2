// This file is part of the course TPV2@UCM - Samir Genaim

#include "AICtrl.h"

#include <cassert>
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

AICtrl::AICtrl() :
		ballTR_(nullptr) {

}

AICtrl::~AICtrl() {
}

void AICtrl::update() {
	auto c = entity_->getComponent<Transform>();

	auto &vel = c->getVel();
	auto &pos = c->getPos();
	auto height = c->getH();

	if (ballComingTowardsPaddle(pos)) {
		float diff = (ballTR_->getPos().getY() + ballTR_->getH() / 2.0f)
				- (pos.getY() + height / 2.0f);
		if (abs(diff) < 10) {
			vel.setY(0.0f);
		} else {
			vel.setY(
					(diff > 0.0f ? 1.0f : -1.0f) * 1.0f
							* ballTR_->getVel().magnitude());
		}
	} else {
		float diff = (sdlutils().height() / 2.0f)
				- (pos.getY() + height / 2.0f);
		if (abs(diff) < 10) {
			vel.setY(0.0);
		} else {
			vel.setY((diff > 0 ? 1 : -1) * 5.0f);
		}
	}
}

void AICtrl::init() {
	ballTR_ = entity_->getMngr()->getHandler<Ball>()->getComponent<Transform>();
	assert(ballTR_ != nullptr);
}

bool AICtrl::ballComingTowardsPaddle(const Vector2D &pos) {

	return (pos.getX() < ballTR_->getPos().getX() && ballTR_->getVel().getX() < 0)
			|| (pos.getX() > ballTR_->getPos().getX()
					&& ballTR_->getVel().getX() > 0);
}
