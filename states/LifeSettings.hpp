#ifndef LIFESETTINGS_HPP
#define LIFESETTINGS_HPP

#include "Menu.hpp"
#include "SDL2/SDL.h"
#include "SDL_ttf.h"

class Life;
class LifeMenu;

class LifeSettings : public Menu
{

public:
	LifeSettings(Life* arg_life, Game* arg_game);
	void renderBg();
	void testNumber();

	void rightAction();
	void leftAction();
	void escapeAction();

private:
	Life* life = nullptr;
	std::array<SDL_Texture*,10> numbers;
};

#endif // LIFESETTINGS_HPP
