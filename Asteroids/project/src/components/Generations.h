#pragma once

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "Transform.h"
#include <iostream>
typedef unsigned int uint;

class Generations : public Component {
public:
	Generations() :
		Component(),
		tr_(nullptr)
	{}

	virtual ~Generations() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		g_ = sdlutils().rand().nextInt(1, 3 + 1);		
		scale();
	}

	void update() override {
		//std::cout << sdlutils().rand().nextInt(0, 3) + 1 << std::endl;
	}

	void scale() {
		tr_->setW(10 + 7.5f * g_);
		tr_->setH(10 + 7.5f * g_);
	}

private:
	Transform* tr_;
	uint g_;
};