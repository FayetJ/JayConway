#ifndef LIFE_HPP
#define LIFE_HPP

#include <array>
#include <iostream>
#include "GameState.hpp"

class Life : public GameState
{
public:
	Life();

	// Routine
	void update(Game* game);
	void render(Game* game);
	void init();
	void cleanup(){};
	void pause(){};
	void resume(){};
	void rightAction(){};
	void leftAction(){};
	void upAction(){};
	void downAction(){};
	void spaceAction(){};
	void escapeAction(){};

	// Get/Set
	bool getCell(int x, int y);
	int getSize();
	int getGen();
	void setSpeed(int ticksPerGen);

	// Life Flow
	void update();
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
	static constexpr int arraySize=24; // Compile-time constant very baaaad
	int m_speed;
	int m_generation;
	int m_tick;
	bool m_running;
	bool m_frozen;
	bool m_paused;
	std::array<std::array<bool,arraySize>,arraySize> m_grid;
	std::array<std::array<bool,arraySize>,arraySize> m_oldGrid;
};

#endif // LIFE_HPP
