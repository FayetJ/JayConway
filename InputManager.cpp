#include "InputManager.hpp"

InputManager::InputManager()
{

}

void InputManager::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RETURN:

					break;

				case SDLK_UP:
					break;

				case SDLK_DOWN:
					break;

				case SDLK_RIGHT:
					break;

				case SDLK_LEFT:
					break;

				case SDLK_SPACE:
					//sendEvent(Event::pause);
					break;

				case SDLK_ESCAPE:
					break;

			}
		}
	}

}

Event InputManager::getEvent(SDL_Event sdlEvent)
{
	return Event::up;
}
