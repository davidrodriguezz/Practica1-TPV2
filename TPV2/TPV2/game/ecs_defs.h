// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
struct Image;
struct FighterCtrlKeys;
struct DeAcceleration;
struct DisableOnExit;
struct Gun;
struct FighterCtrl;
struct ShowAtOppositeSide;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	FighterCtrlKeys,\
	DeAcceleration,\
	DisableOnExit,\
	Gun,\
	FighterCtrl,\
	ShowAtOppositeSide

// groups
struct Fighter;
struct Bullets;
#define _GRPS_LIST_ Fighter, Bullets

// handlers
struct LeftFighter;
struct RightFighter;
#define _HDLRS_LIST_ \
	LeftFighter, \
	RightFighter

// systems
class BallSystem;
class FightersSystem;
class RenderSystem;
class CollisionSystem;
class GameManagerSystem;
class NetworkSystem;

#define _SYS_LIST_ \
		BallSystem, \
		FightersSystem, \
		RenderSystem, \
		CollisionSystem, \
		GameManagerSystem,\
		NetworkSystem
