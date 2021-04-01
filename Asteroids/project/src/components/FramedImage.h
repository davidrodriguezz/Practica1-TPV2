#pragma once

#include "../sdlutils/ecs/Component.h"
#include "Transform.h"
#include "../sdlutils/ecs/Entity.h"
#include "../sdlutils/Texture.h"

typedef unsigned int uint;

class FramedImage : public Component {
public:
	FramedImage(Texture* tex, uint r, uint c) :
		Component(),
		tr_(nullptr), //
		tex_(tex), //
		row(r),
		col(c)
	{}
	virtual ~FramedImage() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void draw(){
		SDL_Rect dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
		SDL_Rect clip = { int(row), int(col), tex_->width() / 4, tex_->height() };
		tex_->render(dest, clip);
	}

	void avanza() { row = row + tex_->height(); };
	bool get() { return (row > 0 && int(row) < tex_->height() * 2); };
	void reset() { row = 0; };
private:
	Transform* tr_;
	Texture* tex_;
	uint row;
	uint col;
};