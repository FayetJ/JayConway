#ifndef LIFEMENU_HPP
#define LIFEMENU_HPP

#include "GameState.hpp"
#include "SDL2/SDL.h"
#include "SDL_ttf.h"
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
	void upAction(){};
	void downAction(){};
	void spaceAction(){};
	void escapeAction();
	void moveUpAction(){};
	void moveDownAction(){};
	void moveLeftAction(){};
	void moveRightAction(){};
	void zoomUpAction(){};
	void zoomDownAction(){};
	void enterAction(){};

private:
	TTF_Font *font = nullptr;
	SDL_Color color = SDL_Color{255,255,255};
	Life* life = nullptr;
	Game* game = nullptr;
	SDL_Rect* fullscreenRect = nullptr;
	SDL_Rect* menuRect = nullptr;
	int scalex = 0;
	int scaley = 0;
	int selector = 0;
};

#endif // LIFEMENU_HPP
