// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
class Rectangle;
class KeyBoardCtrl;
class PaddlePhysics;
class MouseCtrl;
class State;
class BallPhysics;
class GameLogic;
class AICtrl;
struct Image;
// Asteroids
class FighterCtrl;
class ShowAtOppositeSide;
class DisableOnExit;
class DeAcceleration;
class Gun;
class Follow;
class Health;
class FramedImage;
class Generations;
class AsteroidsManager;

#define _CMPS_LIST_  \
	Transform,\
	Rectangle,\
	KeyBoardCtrl,\
	PaddlePhysics,\
	MouseCtrl,\
	State,\
	BallPhysics,\
	GameLogic,\
	AICtrl,\
	Image,\
	FighterCtrl,\
	ShowAtOppositeSide,\
	DisableOnExit,\
	DeAcceleration,\
	Gun,\
	Follow,\
	Health,\
	FramedImage,\
	Generations,\
	AsteroidsManager

// groups
struct Asteroid_grp;
struct Bullet_grp;
#define _GRPS_LIST_  Asteroid_grp,Bullet_grp

// handlers
struct fighter;
#define _HDLRS_LIST_ fighter

// systems
class AsteroidsSystem;
class BulletsSystem;
class FighterSystem;
class FighterGunSystem;
class CollisionSystem;
class GameCtrlSystem;
class RenderSystem;
class CollisionSystem;
#define _SYS_LIST_ \
		AsteroidsSystem, \
		BulletsSystem, \
		FighterSystem, \
		FighterGunSystem, \
		CollisionSystem, \
		GameCtrlSystem, \
		RenderSystem

// messages
#include "messages.h"

class Manager;
class Entity;
class Component;

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type,mngr) GETCMP3(e,type,mngr)
#define GETCMP3(e,type,mngr) mngr->getComponent<type>(e)
