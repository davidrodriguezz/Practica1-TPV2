// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Vector2D;
class Transform;

class AICtrl: public Component {
public:
	AICtrl();
	virtual ~AICtrl();
	void init() override;
	void update() override;
private:
	bool ballComingTowardsPaddle(const Vector2D &pos);
	Transform *ballTR_;
};

