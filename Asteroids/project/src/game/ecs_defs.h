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
	Image

// groups

struct Paddles;
#define _GRPS_LIST_  Paddles

// handlers
struct Ball;
struct LeftPaddle;
struct RightPaddle;
#define _HDLRS_LIST_ Ball,LeftPaddle,RightPaddle
