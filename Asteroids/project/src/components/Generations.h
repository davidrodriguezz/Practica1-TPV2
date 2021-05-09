#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

typedef unsigned int uint;

class Generations : public Component {
public:
	Generations() :
		Component(),
		tr_(nullptr), 
		g_()
	{}

	virtual ~Generations() {
	}

	void init(){
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		g_ = sdlutils().rand().nextInt(1, 3 + 1);
		scale();
	}

	void update(){
		//std::cout << sdlutils().rand().nextInt(0, 3) + 1 << std::endl;
	}

	uint getGen() { return g_; }
	void setGen(uint g) { g_ = g; scale(); }

	void scale() {
		tr_->setW(10 + 7.5f * g_);
		tr_->setH(10 + 7.5f * g_);
	}

private:
	Transform* tr_;
	uint g_;
};