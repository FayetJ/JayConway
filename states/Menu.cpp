#include "Menu.hpp"

Menu::Menu()
{

}

void Menu::init()
{
	t_selected.resize(a_texts.size());
	t_unselected.resize(a_texts.size());
	a_numbers = {"0","1","2","3","4","5","6","7","8","9"};
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
	for (int i=0; i<10; ++i)
	{
		tempSurf = TTF_RenderText_Solid(font, a_numbers[i].c_str(), selected);
		n_selected[i] = SDL_CreateTextureFromSurface(game->renderer,tempSurf);
		tempSurf = TTF_RenderText_Solid(font, a_numbers[i].c_str(), unselected);
		n_unselected[i] = SDL_CreateTextureFromSurface(game->renderer,tempSurf);
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
	menuRect = new SDL_Rect{int(scalex),int(scaley/5),scalex,scaley};
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

void Menu::displayNumber(int number, int x, int y, bool selected)
{
	std::string s_number = std::to_string(number);
	int texW = 0;
	int texH = 0;
	int n = 0;
	for (int i = 0; i<s_number.size(); ++i)
	{
		n = s_number[i]-48;
		SDL_QueryTexture(n_selected[n], NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { x + texW*i, y, texW, texH };
		if (!selected)
		{
			SDL_RenderCopy(game->renderer, n_unselected[n], NULL, &dstrect);
		}
		else
		{
			SDL_RenderCopy(game->renderer, n_selected[n], NULL, &dstrect);
		}
	}
}

void Menu::displayValue(int n, bool selected)
{
	if (values[n] != -1)
	{
		displayNumber(values[n],scalex+300,(100*n)+200,selected);
	}
}

void Menu::displayEntries()
{
	for (int i = 0; i<a_texts.size(); ++i)
	{
		displayEntry(i,scalex+20,(100*i)+200,(selector==i));
		displayValue(i,(selector==i));
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
	clear();
	game->popState();
}
