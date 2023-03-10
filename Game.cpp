#include "Game.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"

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
	inputManager = new(InputManager)(this);
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
		TTF_Init();
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
	SDL_Delay(10); // Delay will be changed to an adaptive sleep() depending on frame time
	currentTime = std::chrono::steady_clock::now();
	while (currentTime - beginTime < deltan)
	{
		currentTime = std::chrono::steady_clock::now();
	}
	beginTime = currentTime;
}

void Game::handleEvents()
{
	inputManager->handleEvents();
}

void Game::update()
{
	states.back()->update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
	states.back()->render();
	SDL_RenderPresent(renderer);
}

void Game::pushState(GameState* state)
{
	states.push_back(state);
	states.back()->init();
}

void Game::popState()
{
	if (!states.empty())
	{
		states.back()->cleanup();
		states.pop_back();
	}
	else
	{
		std::cout << "WARNING : Cant resume or pop state" << std::endl;
	}
}

void Game::changeState(GameState* state)
{
	popState();
	pushState(state);
}

GameState* Game::getCurrentState()
{
	return states.back();
}

void Game::close()
{
	isRunning = false;
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game closed" << std::endl;
}
