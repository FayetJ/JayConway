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

struct Point {
	int x;
	int y;
};

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

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	// Commands


	// Rendering
	void renderLife();
	void drawCell(int x, int y);
	void setFullscreenRect();

	// Cleanup
	void close();

	// Debug
	void debugPrintTick();
	void debugPrintLagSinceBegin();
	void debugPrintLifeTick();
	void debugPrintAsciiLife();
	void debugConsole();
	void debugInit();
	void debugPrintNeighbors(int x, int y);

	bool running() {return isRunning;}

private:
	enum class State
	{
		mainMenu,
		pauseMenu,
		settingsMenu,
		running,
	};

	std::vector<GameState*> states;
	SDL_Rect* fullscreenRect = nullptr;
	State state;
	bool isRunning;
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point beginTime;
	std::chrono::steady_clock::time_point currentTime;
	int currentTick;
	int targetFps;
	std::chrono::duration<int, std::ratio<1,1000000000>> deltan;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Life* life = nullptr;
};

#endif // GAME_HPP
