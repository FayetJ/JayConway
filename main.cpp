#include <iostream>
#include "Game.hpp"
#include "SDL2/SDL.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <unistd.h>
#include "GameState.hpp"
#include "LifeMenu.hpp"
#include "Life.hpp"

Game *game = nullptr;

int main()
{
	int fps = 60;
	game = new Game();
	Life* life = new(Life)(game);
	game->pushState(life);
	game->init("Conway", 0, 0, 800, 600, false, fps);

	while(game->running() == true)
	{
		game->update();
		game->render();
		SDL_Delay(10);
		game->handleEvents();
		game->waitForFrame();
	}
	game->clean();

	return 0;
}
