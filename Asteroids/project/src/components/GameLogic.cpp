// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameLogic.h"

#include <cassert>
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/ecs/Manager.h"
#include "../utils/Collisions.h"
#include "State.h"
#include "Transform.h"
#include "Health.h"

GameLogic::GameLogic() :
		fighter_(nullptr), //
		state_(nullptr) {

}
GameLogic::~GameLogic() {

}

void GameLogic::init() {
	fighter_ = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
	assert(fighter_ != nullptr);

	state_ = entity_->getComponent<State>();
	assert(state_ != nullptr);
}

void GameLogic::update() {

	if (state_->getState() != State::RUNNING)
		return;

	// check if fighter is hit by any asteroid
	for (Entity* e_ : entity_->getMngr()->getEntities())
	{
		if (e_->hasGroup<Asteroid_grp>()) {
			Transform* a_ = e_->getComponent<Transform>();
			if (Collisions::collides(fighter_->getPos(), fighter_->getW(),
				fighter_->getH(), a_->getPos(), a_->getW(), a_->getH())) {

				Health* h_ = fighter_->getEntity()->getComponent<Health>();
				if (h_->getLives() > 0) {
					h_->minusLife();
					a_->getEntity()->setActive(false); // asteroid destruction
				}
				else
					fighter_->getEntity()->setActive(false); // fighter destruction

				sdlutils().soundEffects().at("explosion").play();
			}
		}
	}

	// check if any asteroid is hit by any bullet
	for (Entity* asteroid_ : entity_->getMngr()->getEntities())
	{
		if (asteroid_->hasGroup<Asteroid_grp>()) { 
			Transform* a_ = asteroid_->getComponent<Transform>(); // asteroid
			for (Entity* bullet_ : entity_->getMngr()->getEntities())
			{
				if (bullet_->hasGroup<Bullet_grp>()) {
					Transform* b_ = bullet_->getComponent<Transform>(); // bullet

					if (Collisions::collidesWithRotation(a_->getPos(), a_->getW(), a_->getH(), a_->getRot(),
						b_->getPos(), b_->getW(), b_->getH(), b_->getRot())) {

						a_->getEntity()->setActive(false); // asteroid destruction
						b_->getEntity()->setActive(false); // bullet destruction

						sdlutils().soundEffects().at("explosion").play();
					}
				}
			}
		}
	}
}

/*void GameLogic::onBallExit(Side side) {

	auto &score_ = state_->getScore();
	auto maxScore_ = state_->getMaxScore();

	assert(state_->getState() == State::RUNNING); // this should be called only when game is runnig

	if (side == LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}

	ball_->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	ball_->getVel().set(0, 0);

	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		state_->setState(State::PAUSED);
	else
		state_->setState(State::GAMEOVER);
}*/
