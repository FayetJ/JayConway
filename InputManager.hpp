#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

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
	Event getEvent(SDL_Event sdlEvent);
	void sendEvent(Event event);
};

#endif // INPUTMANAGER_HPP
