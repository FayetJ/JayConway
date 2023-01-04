#include "LifeMenu.hpp"
#include "Life.hpp"

LifeMenu::LifeMenu(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
}

void LifeMenu::init()
{
	a_texts = {"Resume", "Speed", "Settings", "Exit game", "Pain"};
	font = TTF_OpenFont("monobold.ttf",24);
	SDL_Color selected = {0,255,0,0};
	SDL_Color unselected = {255,255,255,0};
	SDL_Surface* tempSurf = nullptr;
	for (int i=0; i<5; ++i)
	{
		tempSurf = TTF_RenderText_Solid(font, a_texts[i].c_str(), selected);
		t_selected[i] = SDL_CreateTextureFromSurface(game->renderer,tempSurf);
		tempSurf = TTF_RenderText_Solid(font, a_texts[i].c_str(), unselected);
		t_unselected[i] = SDL_CreateTextureFromSurface(game->renderer,tempSurf);
	}
}

void LifeMenu::update()
{

}

void LifeMenu::render()
{
	life->render();
	displayBg();
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(game->renderer, fullscreenRect);

	SDL_SetRenderDrawColor(game->renderer,255,0,0,125);
	SDL_RenderFillRect(game->renderer, menuRect);

	displayEntries();
}

void LifeMenu::displayBg()
{
	delete menuRect;
	delete fullscreenRect;
	menuRect = nullptr;
	fullscreenRect = nullptr;
	int w,h;
	SDL_GetWindowSize(game->window, &w, &h);
	scalex = int(w/3);
	scaley = int(h*0.75);
	menuRect = new SDL_Rect{int(scalex),int(scaley/5),scalex,scaley};
	fullscreenRect = new SDL_Rect{0,0,w,h};
	std::cout << "X scale : " << scalex << "\nY scale : " << scaley << std::endl;
}

void LifeMenu::displayEntry(int n, int x, int y, bool selected)
{
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(t_selected[n], NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { x, y, texW, texH };
	if (!selected)
	{
		SDL_RenderCopy(game->renderer, t_unselected[n], NULL, &dstrect);
	}
	else
	{
		SDL_RenderCopy(game->renderer, t_selected[n], NULL, &dstrect);
	}
}

void LifeMenu::displayEntries()
{
	for (int i = 0; i<5; ++i)
	{
		displayEntry(i,scalex+20,(100*i)+200,(selector==i));
	}
}

void LifeMenu::downAction()
{
	selector++;
	selector=selector%5;
}

void LifeMenu::upAction()
{
	selector=((selector-1) % 5 + 5) % 5;
}

void LifeMenu::escapeAction()
{
	game->popState();
}
