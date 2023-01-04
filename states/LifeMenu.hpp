#ifndef LIFEMENU_HPP
#define LIFEMENU_HPP

#include "GameState.hpp"
#include "SDL2/SDL.h"
#include "SDL_ttf.h"
#include <string.h>
#include <array>
#include <iostream>

class Life;

class LifeMenu : public GameState
{
public:
	LifeMenu(Life* arg_life, Game* arg_game);

	// Boilerplate
	void update();
	void render();
	void init();
	void cleanup(){};
	void pause(){};
	void resume(){};

	// Inputs
	void rightAction(){};
	void leftAction(){};
	void upAction();
	void downAction();
	void spaceAction(){};
	void escapeAction();
	void moveUpAction(){};
	void moveDownAction(){};
	void moveLeftAction(){};
	void moveRightAction(){};
	void zoomUpAction(){};
	void zoomDownAction(){};
	void enterAction(){};

	void click(int x, int y){};

	// Menu Display
	void displayEntry(int n, int x, int y, bool selected);
	void displayBg();
	void displayEntries();

private:
	TTF_Font *font = nullptr;
	SDL_Color color = SDL_Color{255,255,255};
	std::array<SDL_Texture*,5> t_unselected;
	std::array<SDL_Texture*,5> t_selected;
	std::array<std::string,5> a_texts;
	Life* life = nullptr;
	Game* game = nullptr;
	SDL_Rect* fullscreenRect = nullptr;
	SDL_Rect* menuRect = nullptr;
	int scalex = 0;
	int scaley = 0;
	int tscalex = 0;
	int tscaley = 0;
	int selector = 0;
};

#endif // LIFEMENU_HPP
