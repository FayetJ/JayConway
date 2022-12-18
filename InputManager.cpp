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
				case up:
					game->getCurrentState()->upAction();
					break;

				case down:
					game->getCurrentState()->downAction();
					break;

				case right:
					game->getCurrentState()->rightAction();
					break;

				case left:
					game->getCurrentState()->leftAction();
					break;

				case space:
					game->getCurrentState()->spaceAction();
					break;

				case escape:
					game->getCurrentState()->escapeAction();
					break;

				default:
					break;
			}
			if (event.key.keysym.sym == moveUp)
			{
				game->getCurrentState()->moveUpAction();
			}
			else if (event.key.keysym.sym == moveDown)
			{
				game->getCurrentState()->moveDownAction();
			}
			else if (event.key.keysym.sym == moveLeft)
			{
				game->getCurrentState()->moveLeftAction();
			}
			else if (event.key.keysym.sym == moveRight)
			{
				game->getCurrentState()->moveRightAction();
			}
			else if (event.key.keysym.sym == enter)
			{
				game->getCurrentState()->enterAction();
			}

		}
		if (event.type == SDL_QUIT)
		{
			game->close();
		}
	}
}
