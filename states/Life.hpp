#ifndef LIFE_HPP
#define LIFE_HPP

#include <array>
#include <iostream>
#include "GameState.hpp"
#include "Game.hpp"
#include "LifeMenu.hpp"

class Life : public GameState
{
public:
	Life(Game* arg_game);

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
	void spaceAction();
	void escapeAction();
	void moveUpAction();
	void moveDownAction();
	void moveLeftAction();
	void moveRightAction();
	void zoomUpAction();
	void zoomDownAction();
	void enterAction();

	// Get/Set
	bool getCell(int x, int y);
	int getGen();
	void setSpeed(int ticksPerGen);

	// Life Flow
	void nextGen();
	void pauseGame(bool paused);
	void freezeSimulation(bool frozen);
	void toggleFrozen();
	void togglePause();
	void generatePreset(int preset);

	// Grid
	void resizeGrid(int x, int y);

	// Create Shapes
	int createGlider(int x, int y);
	int createBlinker(int x, int y);
	int createPentaDecathlon(int x, int y);


private:
	int scale = 30;
	SDL_Point offset = SDL_Point{0,0};
	Game* game = nullptr;
	LifeMenu* menu = nullptr;
	int m_speed = 20;
	int m_generation = 0;
	int m_tick = 0;
	bool m_frozen = false;
	bool m_paused = false;
	SDL_Point size = SDL_Point{20,20};
	std::vector<std::vector<bool>> m_grid;
	std::vector<std::vector<bool>> m_oldGrid;

};

#endif // LIFE_HPP
