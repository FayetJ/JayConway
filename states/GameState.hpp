#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Game.hpp"


class GameState
{
public:
	GameState();
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	// Routine
	virtual void update() = 0;
	virtual void render() = 0;

	void changeState(Game* game, GameState* state)
	{
		game->changeState(state);
	}

	// KB Inputs
	virtual void rightAction() = 0;
	virtual void leftAction() = 0;
	virtual void upAction() = 0;
	virtual void downAction() = 0;
	virtual void spaceAction() = 0;
	virtual void enterAction() = 0;
	virtual void moveUpAction() = 0;
	virtual void moveDownAction() = 0;
	virtual void moveLeftAction() = 0;
	virtual void moveRightAction() = 0;
	virtual void zoomUpAction() = 0;
	virtual void zoomDownAction() = 0;
	virtual void escapeAction(){};
	virtual void clear() = 0;

	// Mouse Inputs
	virtual void click(int x, int y) = 0;
};

#endif // GAMESTATE_HPP
