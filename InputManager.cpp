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
				moveUpHeld = true;
			}
			else if (event.key.keysym.sym == moveDown)
			{
				moveDownHeld = true;
			}
			else if (event.key.keysym.sym == moveLeft)
			{
				moveLeftHeld = true;
			}
			else if (event.key.keysym.sym == moveRight)
			{
				moveRightHeld = true;
			}
			else if (event.key.keysym.sym == zoomUp)
			{
				zoomUpHeld = true;
			}
			else if (event.key.keysym.sym == zoomDown)
			{
				zoomDownHeld = true;
			}
			else if (event.key.keysym.sym == enter)
			{
				game->getCurrentState()->enterAction();
			}

		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == moveUp)
			{
				moveUpHeld = false;
			}
			else if (event.key.keysym.sym == moveDown)
			{
				moveDownHeld = false;
			}
			else if (event.key.keysym.sym == moveLeft)
			{
				moveLeftHeld = false;
			}
			else if (event.key.keysym.sym == moveRight)
			{
				moveRightHeld = false;
			}
			else if (event.key.keysym.sym == zoomUp)
			{
				zoomUpHeld = false;
			}
			else if (event.key.keysym.sym == zoomDown)
			{
				zoomDownHeld = false;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int x,y;
			SDL_GetMouseState(&x,&y);
			game->getCurrentState()->click(x,y);
		}

		if (event.type == SDL_QUIT)
		{
			game->close();
		}
	}
	sendHeldKeys();
}

void InputManager::sendHeldKeys()
{
	if (moveUpHeld)
	{
		game->getCurrentState()->moveUpAction();
	}
	if (moveDownHeld)
	{
		game->getCurrentState()->moveDownAction();
	}
	if (moveLeftHeld)
	{
		game->getCurrentState()->moveLeftAction();
	}
	if (moveRightHeld)
	{
		game->getCurrentState()->moveRightAction();
	}
	if (zoomUpHeld)
	{
		game->getCurrentState()->zoomUpAction();
	}
	if (zoomDownHeld)
	{
		game->getCurrentState()->zoomDownAction();
	}
}
