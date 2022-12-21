#ifndef GAME_HPP
#define GAME_HPP

#include "SDL2/SDL.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ratio>
#include <array>
#include <vector>

class GameState;
class InputManager;

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
	GameState* getCurrentState();

	// Commands


	// Rendering

	// Cleanup
	void close();

	// Debug

	bool running() {return isRunning;}

	SDL_Window* window;
	SDL_Renderer* renderer;

private:
	// Window Handling
	bool isRunning;

	// Time Handling
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point beginTime;
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::duration<int, std::ratio<1,1000000000>> deltan;

	InputManager* inputManager;
	std::vector<GameState*> states;
	int currentTick;
	int targetFps;
};

#endif // GAME_HPP
