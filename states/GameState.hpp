#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Game.hpp"


class GameState
{
public:
	GameState();

	// Initialization and destruction
	virtual void init(){};
	virtual void cleanup(){};

	// Routine
	virtual void update(){};
	virtual void render(){};

	void changeState(Game* game, GameState* state)
	{
		game->changeState(state);
	}

	// Keyboard Inputs
	virtual void rightAction(){};
	virtual void leftAction(){};
	virtual void upAction(){};
	virtual void downAction(){};
	virtual void spaceAction(){};
	virtual void enterAction(){};
	virtual void moveUpAction(){};
	virtual void moveDownAction(){};
	virtual void moveLeftAction(){};
	virtual void moveRightAction(){};
	virtual void zoomUpAction(){};
	virtual void zoomDownAction(){};
	virtual void escapeAction(){};
	virtual void delAction(){};

	// Mouse Inputs
	virtual void click(int x, int y){};
};

#endif // GAMESTATE_HPP
