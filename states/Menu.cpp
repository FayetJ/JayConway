#include "Menu.hpp"

Menu::Menu()
{

}

void Menu::init()
{
	t_selected.resize(a_texts.size());
	t_unselected.resize(a_texts.size());
	font = TTF_OpenFont("monobold.ttf",24);
	SDL_Color selected = {0,255,0,0};
	SDL_Color unselected = {255,255,255,0};
	SDL_Surface* tempSurf = nullptr;
	for (int i=0; i<a_texts.size(); ++i)
	{
		tempSurf = TTF_RenderText_Solid(font, a_texts[i].c_str(), selected);
		t_selected[i] = SDL_CreateTextureFromSurface(game->renderer,tempSurf);
		tempSurf = TTF_RenderText_Solid(font, a_texts[i].c_str(), unselected);
		t_unselected[i] = SDL_CreateTextureFromSurface(game->renderer,tempSurf);
	}
}

void Menu::update()
{

}

void Menu::render()
{
	delete menuRect;
	delete fullscreenRect;
	menuRect = nullptr;
	fullscreenRect = nullptr;
	int w,h;
	SDL_GetWindowSize(game->window, &w, &h);
	scalex = int(w/3);
	scaley = int(h*0.75);
	menuRect = new SDL_Rect{int(scalex),int(scaley/a_texts.size()),scalex,scaley};
	fullscreenRect = new SDL_Rect{0,0,w,h};

	renderBg();
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(game->renderer, fullscreenRect);

	SDL_SetRenderDrawColor(game->renderer,0,0,0,255);
	SDL_RenderFillRect(game->renderer, menuRect);

	SDL_SetRenderDrawColor(game->renderer,255,255,255,255);
	SDL_RenderDrawRect(game->renderer, menuRect);

	displayEntries();
}

void Menu::displayEntry(int n, int x, int y, bool selected)
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

void Menu::displayEntries()
{
	for (int i = 0; i<a_texts.size(); ++i)
	{
		displayEntry(i,scalex+20,(100*i)+200,(selector==i));
	}
}

void Menu::downAction()
{
	selector++;
	selector=selector%a_texts.size();
}

void Menu::upAction()
{
	int a = a_texts.size();
	selector=((selector-1) % a + a) % a;
}

void Menu::escapeAction()
{
	game->popState();
}
