#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Game.hpp"


class GameState
{
public:
	GameState();
	virtual void init(){};
	virtual void cleanup(){};

	virtual void pause(){};
	virtual void resume(){};

	// Routine
	virtual void update(){};
	virtual void render(){};

	void changeState(Game* game, GameState* state)
	{
		game->changeState(state);
	}

	// KB Inputs
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
	virtual void clear(){};

	// Mouse Inputs
	virtual void click(int x, int y) = 0;
};

#endif // GAMESTATE_HPP
