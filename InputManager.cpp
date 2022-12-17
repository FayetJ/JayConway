#include "InputManager.hpp"

InputManager::InputManager(Game* arg_game)
{
	game=arg_game;
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

				case up:
					game->getCurrentState()->upAction();
					break;

				case SDLK_DOWN:
					game->getCurrentState()->downAction();
					break;

				case right:
					game->getCurrentState()->rightAction();
					break;

				case SDLK_LEFT:
					game->getCurrentState()->leftAction();
					break;

				case space:
					game->getCurrentState()->spaceAction();
					break;

				case escape:
					game->getCurrentState()->escapeAction();
					break;

			}
		}
		if (event.type == SDL_QUIT)
		{
			game->close();
		}
	}
}
