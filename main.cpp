#include <iostream>
#include "Game.hpp"
#include "SDL2/SDL.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <unistd.h>

Game *game = nullptr;

int main()
{
	int fps = 60;
	game = new Game();
	game->init("Conway", 0, 0, 800, 600, false, fps);

	while(game->running() == true)
	{
		game->update();
		game->render();
		SDL_Delay(12);
		game->waitForFrame();
	}
	game->clean();

	return 0;
}
