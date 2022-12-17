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
	InputManager();
	void handleEvents();

private:
	Game *game;
	static const int up = SDLK_UP;
	static const int right = SDLK_RIGHT;
	static const int space = SDLK_SPACE;
	static const int escape = SDLK_ESCAPE;

};

#endif // INPUTMANAGER_HPP
