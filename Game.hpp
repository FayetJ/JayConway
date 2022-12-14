#ifndef GAME_HPP
#define GAME_HPP

#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ratio>
#include <array>
#include <vector>
#include "Life.hpp"

class GameState;

class Game
{
public:

	// INIT
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int argTargetFps=60);

	// Routine
	void waitForFrame();
	void handleEvents();
	void update();
	void render();
	void clean();

	// State Handling
	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	// Commands

	// Rendering

	// Cleanup
	void close();

	// Debug

	bool running() {return isRunning;}

private:
	// Window Handling
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Time Handling
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point beginTime;
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::duration<int, std::ratio<1,1000000000>> deltan;

	std::vector<GameState*> states;
	int currentTick;
	int targetFps;
};

#endif // GAME_HPP
