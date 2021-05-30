// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
struct Image;
// Asteroids
class FighterCtrl;
class ShowAtOppositeSide;
class DisableOnExit;
class DeAcceleration;
class Gun;
//class Follow;
class Health;
class FramedImage;
//class Generations;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	FighterCtrl,\
	ShowAtOppositeSide,\
	DisableOnExit,\
	DeAcceleration,\
	Gun,\
	Health,\
	FramedImage,\

// groups
//struct Asteroid_grp;
struct Bullet_grp;
#define _GRPS_LIST_ Bullet_grp

// handlers
struct fighter1;
struct fighter2;
#define _HDLRS_LIST_ fighter1, fighter2

// systems
//class AsteroidsSystem;
class BulletsSystem;
class FighterSystem;
class FighterGunSystem;
class CollisionsSystem;
class GameManagerSystem;
class RenderSystem;
#define _SYS_LIST_ \
		BulletsSystem, \
		FighterSystem, \
		FighterGunSystem, \
		CollisionsSystem, \
		GameManagerSystem, \
		RenderSystem

// messages
#include "messages.h"

class Manager;
struct Entity;
struct Component;

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type,mngr) GETCMP3(e,type,mngr)
#define GETCMP3(e,type,mngr) mngr->getComponent<type>(e)
