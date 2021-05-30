// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameManagerSystem.h"
struct Entity;

enum MsgId : Uint8 {
	_BULLET_SHOOT,		// fighter dispara un bullet
	//_BULLET_ASTEROID,	// colisionan un bullet y un asteroid
	//_FIGHTER_ASTEROID,	// colisionan fighter y un asteroid
	_PAUSE_START,		// entra en pausa
	_PAUSE_OVER,		// termina la pausa
	_GAME_OVER,			// partida terminada: todos los asteroides destruidos
	_NEW_GAME,			// comienza una partida nueva
	_LOSE_LIFE,			// comienza una partida nueva
	_BULLET_FIGHTER
};

struct Collision {
	Entity* a;
	Entity* b;
};

struct Condition {
	bool data;
};

struct SomeOtherMsg { // just for the example
	int otherData_;
};

struct Message {
	MsgId id_;
	union {
		Condition c_;
		Collision col_;
		SomeOtherMsg otherMsg_; 
	};
};
