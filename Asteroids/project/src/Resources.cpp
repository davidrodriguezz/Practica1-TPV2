#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Airplanes, "resources/images/airplanes.png" }, //
		{ Asteroid, "resources/images/asteroid.png" }, //
		{ Heart, "resources/images/heart.png" }, //
		{ WhiteRect, "resources/images/whiterect.png" }, //
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }, //
		{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOverWon, "Game Over! You Won!", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ GameOverLost, "Game Over! You Lost!", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ ImperialMarch, "resources/sound/imperial_march.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Explosion, "resources/sound/explosion.wav" }, //
		{ GunShot, "resources/sound/GunShot.wav" } //
};

