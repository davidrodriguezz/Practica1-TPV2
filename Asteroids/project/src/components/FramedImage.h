#pragma once

#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/VirtualTimer.h"

typedef unsigned int uint;

class FramedImage : public Component {
public:
	FramedImage(Texture* tex, Transform* tr) :
		Component(),
		tr_(tr), //
		tex_(tex), col(), row(), time()
	{
		init();
	}

	virtual ~FramedImage() {
	}

	void init() {
		row = col = 0;
		time = new VirtualTimer();
		assert(tr_ != nullptr);
	}

	void render() {
		SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);		
		SDL_Rect clip = build_sdlrect(float(row), float(col), tex_->width() / 6.0f, tex_->height() / 5.0f);
		tex_->render(clip, dest, tr_->rotation_);
	}
	
	void update() {
		if (time->currTime() >= 50) {
			avanza();
			tr_->rotation_ = tr_->rotation_ + 1.0f;
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