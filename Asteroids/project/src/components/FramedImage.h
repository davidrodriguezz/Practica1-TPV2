#pragma once

#include "../sdlutils/ecs/Component.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../sdlutils/VirtualTimer.h"

typedef unsigned int uint;

class FramedImage : public Component {
public:
	FramedImage(Texture* tex) :
		Component(),
		tr_(nullptr), //
		tex_(tex), col(), row(), time()
	{}

	virtual ~FramedImage() {
	}

	void init() override {
		row = col = 0;
		time = new VirtualTimer();
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());		
		SDL_Rect clip = build_sdlrect(float(row), float(col), tex_->width() / 6.0f, tex_->height() / 5.0f);
		tex_->render(clip, dest, tr_->getRot());
	}
	
	void update() override {
		if (time->currTime() >= 50) {
			avanza();
			tr_->setRot(tr_->getRot() + 1.0f);
			time->reset();
		}
	}

	void avanza() { 
		if (row < tex_->width() * (5.0f / 6.0f)) {
			row = row + tex_->width() / 6.0f;
		}
		else if (col < tex_->height() * (4.0f / 5.0f)) {
			row = 0;
			col = col + tex_->width() / 5.0f;
		}
		else {
			row = 0;
			col = 0;
		}
	}

private:
	Transform* tr_;
	Texture* tex_;
	float row;
	float col;
	VirtualTimer* time;
};