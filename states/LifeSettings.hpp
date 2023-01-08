#ifndef LIFESETTINGS_HPP
#define LIFESETTINGS_HPP

#include "Menu.hpp"
#include "Life.hpp"
#include "SDL2/SDL.h"
#include "SDL_ttf.h"


class LifeSettings : public Menu
{

public:
	LifeSettings();

private:
	Life* life = nullptr;
};

#endif // LIFESETTINGS_HPP
