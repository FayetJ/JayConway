#ifndef LIFEMENU_HPP
#define LIFEMENU_HPP

#include "GameState.hpp"
#include <array>
#include <iostream>

class LifeMenu : public GameState
{
public:
	LifeMenu();

	// Routine
	void update(Game* game);
	void render(Game* game);
	void init(){};
	void cleanup(){};
	void pause(){};
	void resume(){};
	void rightAction(){};
	void leftAction(){};
	void upAction(){};
	void downAction(){};
	void spaceAction(){};
	void escapeAction(){};

private:

};

#endif // LIFEMENU_HPP
