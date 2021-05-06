// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;
class SoundEffect;

class BallSystem: public System {
public:
	BallSystem();
	virtual ~BallSystem();
	void init() override;
	void update() override;

	void resetBall();
	void initBall();
	void receive(const Message&) override;

private:
	Transform *ballTr_;
	SoundEffect *wallHit_;
};

