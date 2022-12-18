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
	int getSize();
	int getGen();
	void setSpeed(int ticksPerGen);

	// Life Flow
	void nextGen();
	void pauseGame(bool paused);
	void freezeSimulation(bool frozen);
	void toggleFrozen();
	void togglePause();
	void generatePreset(int preset);

	// Create Shapes
	int createGlider(int x, int y);
	int createBlinker(int x, int y);
	int createPentaDecathlon(int x, int y);


private:
	int scale = 30;
	SDL_Point offset = SDL_Point{0,0};
	Game* game = nullptr;
	LifeMenu* menu = nullptr;
	static constexpr int arraySize=24; // Compile-time constant very baaaad
	int m_speed = 20;
	int m_generation = 0;
	int m_tick = 0;
	bool m_frozen = false;
	bool m_paused = false;
	std::array<std::array<bool,arraySize>,arraySize> m_grid;
	std::array<std::array<bool,arraySize>,arraySize> m_oldGrid;
};

#endif // LIFE_HPP
