#include "LifeMenu.hpp"
#include "Life.hpp"

LifeMenu::LifeMenu(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
}

void LifeMenu::init()
{
	font = TTF_OpenFont("monobold.ttf",26);
}

void LifeMenu::update()
{

}

void LifeMenu::render()
{
	int w,h;
	SDL_GetWindowSize(game->window, &w, &h);
	scalex = int(w/2);
	scaley = int((h/4)*3);
	delete fullscreenRect;
	delete menuRect;
	menuRect = nullptr;
	fullscreenRect = nullptr;
	menuRect = new SDL_Rect{int(scalex/4),int(scaley/4),scalex,scaley};
	fullscreenRect = new SDL_Rect{0,0,w,h};

	life->render();
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(game->renderer, fullscreenRect);

	SDL_SetRenderDrawColor(game->renderer,255,0,0,125);
	SDL_RenderFillRect(game->renderer, menuRect);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "put your text here", color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(game->renderer, surfaceMessage);
	SDL_RenderCopy(game->renderer, Message, NULL, menuRect);
}

void LifeMenu::escapeAction()
{
	game->popState();
}
