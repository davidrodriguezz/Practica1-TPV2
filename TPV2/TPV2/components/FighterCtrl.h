#pragma once

#include "../ecs/Component.h"
#include "Transform.h"
#include "FighterCtrlKeys.h"

class SoundEffect;

struct FighterCtrl : Component {
public:
	FighterCtrl(Transform* tr, FighterCtrlKeys* keys) :
		tr_(tr), keys_(keys), speedlimit_(3.0f), thrust_(0.2f)/*, thrustSound_(nullptr)*/ {
	}

	virtual ~FighterCtrl() {}

	void init();
	void update();

private:
	FighterCtrlKeys* keys_;
	Transform* tr_;
	float speedlimit_;
	float thrust_;

	//SoundEffect* thrustSound_;
};