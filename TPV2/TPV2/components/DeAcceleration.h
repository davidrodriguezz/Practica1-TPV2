#pragma once

#include "../ecs/Component.h"
#include "Transform.h"

struct DeAcceleration : Component {
public:
	DeAcceleration(Transform* tr) :
		tr_(tr) {
	}
	virtual ~DeAcceleration() {
	}

	void init() {
		assert(tr_ != nullptr);
	}

	void update(){
		tr_->vel_.set(tr_->vel_ * 0.995f);
	}

private:
	Transform* tr_;
}
;