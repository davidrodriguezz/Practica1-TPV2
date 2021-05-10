#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

typedef unsigned int uint;

class Generations : public Component {
public:
	Generations(Transform* tr) :
		Component(),
		tr_(tr), 
		g_()
	{}

	virtual ~Generations() {
	}

	void init(){
		assert(tr_ != nullptr);
		g_ = sdlutils().rand().nextInt(1, 3 + 1);
		scale();
	}

	uint getGen() { return g_; }
	void setGen(uint g) { g_ = g; scale(); }

	void scale() {
		tr_->width_ = (10 + 7.5f * g_);
		tr_->height_ = (10 + 7.5f * g_);
	}

private:
	Transform* tr_;
	uint g_;
};