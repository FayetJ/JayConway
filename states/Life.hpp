#ifndef LIFE_HPP
#define LIFE_HPP

#include <array>
#include <iostream>
#include "GameState.hpp"


// Will change to be a gamestate
class Life : public GameState
{

public:

	Life();
	~Life();


	void init(int preset=0);
	bool getCell(int x, int y);
	int getSize();
	int getGen();
	void setSpeed(int ticksPerGen);
	int createGlider(int x, int y);
	int createBlinker(int x, int y);
	int createPentaDecathlon(int x, int y);
	void update();
	void nextGen();
	void pauseGame(bool paused);
	void freezeSimulation(bool frozen);
	void toggleFrozen();
	void togglePause();
	void generatePreset(int preset);



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
