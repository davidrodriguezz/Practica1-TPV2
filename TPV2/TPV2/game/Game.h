// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <memory>



// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class System;

class Game {
public:
	Game();
	virtual ~Game();
	void init(const char *host, Uint16 port);
	void start();
private:
	std::unique_ptr<Manager> mngr_;
	System *bulletsSys_;
	System *fightersSys_;
	System *fighterGunSys_;
	System *collisionsSys_;
	System *gameMngrSys_;
	System *renderSys_;
	System *networkSys_;
};

static void limpiar_pantalla()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
