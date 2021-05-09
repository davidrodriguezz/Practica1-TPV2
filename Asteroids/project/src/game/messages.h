// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameCtrlSystem.h"

enum MsgId : Uint8 {
	_BULLET_SHOOT,		// fighter dispara un bullet
	_BULLET_ASTEROID,	// colisionan un bullet y un asteroid
	_FIGHTER_ASTEROID,	// colisionan fighter y un asteroid
	_ROUND_START,		// comienza la accion
	_PAUSE_START,		// entra en pausa
	_PAUSE_OVER,		// termina la pausa
	_ROUND_OVER,		// todos los asteroides destruidos
	_GAME_OVER,			// te quedas sin vidas
	_GAME_COMPLETE		// juego completado
};

//struct BallExitMsg {
//	GameCtrlSystem::Side side_;
//};

struct SomeOtherMsg { // just for the example
	int otherData_;
};

struct Message {
	MsgId id_;
	union {
		//BallExitMsg ballExit_;
		SomeOtherMsg otherMsg_; // just for the example
	};
};
