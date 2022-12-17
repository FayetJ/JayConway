#include "Game.hpp"

Game::Game()
{
	startTime = std::chrono::steady_clock::now();
	beginTime = startTime;
	currentTick = 0;
}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int argTargetFps)
{
	state = State::mainMenu;
	life = new Life();
	life->init(1);
	targetFps = argTargetFps;
	deltan = std::chrono::duration<int, std::ratio<1,1000000000>> (1000000000/targetFps);
	int flags = 0;
	flags = flags | SDL_WINDOW_RESIZABLE;
	if(fullscreen)
	{
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}
	if(!SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "Subsystems initialized..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	} else {isRunning = false;}
}

void Game::waitForFrame()
{
	currentTime = std::chrono::steady_clock::now();
	while (currentTime - beginTime < deltan)
	{
		currentTime = std::chrono::steady_clock::now();
	}
	beginTime = currentTime;
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning=false;
		}

		if (event.type == SDL_KEYDOWN)
		{
			switch (state)
			{
				case State::running:
					switch(event.key.keysym.sym)
					{
						case SDLK_SPACE:
							life->toggleFrozen();
							break;

						case SDLK_ESCAPE:
							life->pauseGame(true);
							state = State::pauseMenu;
							break;

						case SDLK_RIGHT:
							life->nextGen();
							break;

						default:
							break;
					}
					break;

				case State::mainMenu:
					switch(event.key.keysym.sym)
					{
						case SDLK_RETURN:
							life->init(2);
							state = State::running;
							break;
						default:
							break;
					}
					break;

				case State::pauseMenu:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							life->pauseGame(false);
							state = State::running;
							break;
						default:
							break;
					}
					break;
				default:
					break;

			}

		}
	}
}

void Game::update()
{
	life->update();
	++currentTick;
}

void Game::drawCell(int x, int y)
{
	int scale = 35;
	bool alive = life->getCell(x,y);
	SDL_Rect cell {x*scale-x,y*scale-y,scale,scale};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (alive)
	{
		SDL_RenderFillRect(renderer,&cell);
	}
	else if(!alive)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer,&cell);
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer,&cell);
}

void Game::render()
{
	setFullscreenRect();
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
	renderLife();
	switch (state)
	{
		case State::mainMenu:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
			SDL_RenderFillRect(renderer, fullscreenRect);
			break;

		case State::running:
			break;

		case State::pauseMenu:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
			SDL_RenderFillRect(renderer, fullscreenRect);
			break;

		case State::settingsMenu:
			break;
	}
	SDL_RenderPresent(renderer);
}

void Game::renderLife()
{
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(window,&w,&h);
	for (int i = 0 ; i<life->getSize() ; ++i)
	{
		for (int j = 0 ; j<life->getSize() ; ++j)
		{
			drawCell(i,j);
		}
	}

}

void Game::setFullscreenRect()
{
	int w,h;
	SDL_GetWindowSize(window, &w, &h);
	delete fullscreenRect;
	fullscreenRect = nullptr;
	fullscreenRect = new SDL_Rect{0,0,w,h};
}

void Game::close()
{
	isRunning = false;
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game closed" << std::endl;
}

void Game::debugPrintTick()
{
	std::cout << "Current tick : " << currentTick << std::endl;
}

void Game::debugPrintLifeTick()
{
	std::cout << "Life tick : " << life->getGen() << std::endl;
}

void Game::debugPrintAsciiLife()
{
	std::cout << "LIFE UPDATE !!! \nGeneration n°" << life->getGen() << std::endl;
	for (int i = 0 ; i < life->getSize() ; ++i)
	{
		for (int j = 0 ; j < life->getSize() ; ++j)
		{
			if (life->getCell(j,i))
			{
				std::cout << "0";
			}
			else
			{
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "\n \n \n";
}

void Game::debugConsole()
{

}

void Game::debugPrintNeighbors(int x, int y)
{
	int size = life->getSize();
	int xp = (x+1)%size;
	int yp = (y+1)%size;
	int ym = ((y-1) % size + size) % size;
	int xm = ((x-1) % size + size) % size;
	std::cout << "Neighbors of [" << x << "][" << y << "]\n"
			  << "[" << xm << "][" << ym << "] "
			  << "[" << x << "][" << ym << "] "
			  << "[" << xp << "][" << ym << "] \n"
			  << "[" << xm << "][" << y << "] "
			  << "[" << xp << "][" << y << "] \n"
			  << "[" << xm << "][" << yp << "] "
			  << "[" << x << "][" << yp << "] "
			  << "[" << xp << "][" << yp << "] \n"
			  << std::endl;
}

void Game::debugPrintLagSinceBegin() // Marginally working
{
	std::chrono::duration<int, std::ratio<1,1000000000>> timeSinceStart = currentTime - startTime;
	long int lag = timeSinceStart.count() - (currentTick*16666666);
	std::cout << lag << std::endl;
}


