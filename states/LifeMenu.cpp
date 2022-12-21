#include "LifeMenu.hpp"
#include "Life.hpp"

LifeMenu::LifeMenu(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
	font = TTF_OpenFont("monobold.ttf",50);
}

void LifeMenu::init()
{

}

void LifeMenu::update()
{

}

void LifeMenu::render()
{
	SDL_Surface * surface = TTF_RenderText_Solid(font,
	  "DOING", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(game->renderer,
	  surface);
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
	SDL_RenderCopy(game->renderer, texture, NULL, menuRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void LifeMenu::escapeAction()
{
	game->popState();
}
