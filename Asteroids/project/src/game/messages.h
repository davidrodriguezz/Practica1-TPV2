// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameCtrlSystem.h"
class Entity;
//#include "../ecs/Entity.h"

enum MsgId : Uint8 {
	_BULLET_SHOOT,		// fighter dispara un bullet
	_BULLET_ASTEROID,	// colisionan un bullet y un asteroid
	_FIGHTER_ASTEROID,	// colisionan fighter y un asteroid
	_ROUND_START,		// comienza la accion
	_PAUSE_START,		// entra en pausa
	_PAUSE_OVER,		// termina la pausa
	_ROUND_OVER,		// todos los asteroides destruidos
	_GAME_OVER,			// partida terminada
	_NEW_GAME			// nueva partida
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
