#ifndef LIFEMENU_HPP
#define LIFEMENU_HPP

#include "Menu.hpp"
#include "GameState.hpp"
#include "SDL2/SDL.h"
#include "SDL_ttf.h"
#include <string.h>
#include <array>
#include <iostream>
#include "LifeSettings.hpp"

class Life;

class LifeMenu : public Menu
{
public:
	LifeMenu(Life* arg_life, Game* arg_game);

	// Boilerplate
	void cleanup(){};

	// Inputs
	void enterAction();

	void click(int x, int y){};

	// Menu Display
	void renderBg();

private:
	Life* life = nullptr;
	LifeSettings* settings = nullptr;
};

#endif // LIFEMENU_HPP
