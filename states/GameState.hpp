#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Game.hpp"


class GameState
{
public:
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	// Routine
	virtual void handleEvents(Game* game) = 0;
	virtual void update(Game* game) = 0;
	virtual void render(Game* game) = 0;

	void changeState(Game* game,GameState* state)
	{
		game->changeState(state);
	}

	// Inputs
	virtual void rightAction() = 0;
	virtual void leftAction() = 0;
	virtual void upAction() = 0;
	virtual void downAction() = 0;
	virtual void spaceAction() = 0;
	virtual void escapeAction() = 0;

	protected: GameState() {}
};

#endif // GAMESTATE_HPP
