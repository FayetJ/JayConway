#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "GameState.hpp"
#include "Game.hpp"
#include "SDL.h"

enum class Event
{
	up,down,left,right,
	pause,
};

class InputManager
{
public:
	InputManager(Game* arg_game);
	void handleEvents();
	void sendHeldKeys();

private:
	Game *game = nullptr;

	// INPUTS
	static const int up = SDLK_UP;
	static const int down = SDLK_DOWN;
	static const int right = SDLK_RIGHT;
	static const int left = SDLK_LEFT;
	static const int space = SDLK_SPACE;
	static const int escape = SDLK_ESCAPE;
	static const int del = SDLK_DELETE;
	int enter = SDLK_RETURN;
	int moveUp = SDLK_z;
	int moveDown = SDLK_s;
	int moveLeft = SDLK_q;
	int moveRight = SDLK_d;
	int zoomUp = SDLK_UP;
	int zoomDown = SDLK_DOWN;

	// KEY MEMORY
	bool moveUpHeld = false;
	bool moveDownHeld = false;
	bool moveLeftHeld = false;
	bool moveRightHeld = false;
	bool zoomUpHeld = false;
	bool zoomDownHeld = false;
};

#endif // INPUTMANAGER_HPP
