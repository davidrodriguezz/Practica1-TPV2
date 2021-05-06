// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>



// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class System;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	std::unique_ptr<Manager> mngr_;
	System *AsteroidsSystem_;
	System *BulletsSystem_;
	System *FighterSystem_;
	System *FighterGunSystem_;
	System *CollisionSystem_;
	System *GameCtrlSystem_;
	System *RenderSystem_;
};
