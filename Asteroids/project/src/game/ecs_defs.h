// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Rectangle;
class KeyBoardCtrl;
class PaddlePhysics;
class MouseCtrl;
class State;
class BallPhysics;
class GameLogic;
class AICtrl;
class Image;
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
	Generations



// groups

struct Paddles;
#define _GRPS_LIST_  Paddles//, Asteroid_grp, Bullet_grp

// handlers
struct Ball;
struct LeftPaddle;
struct RightPaddle;
struct Fighter;
#define _HDLRS_LIST_ Ball,LeftPaddle,RightPaddle,Fighter

