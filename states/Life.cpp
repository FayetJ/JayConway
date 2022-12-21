#include "Life.hpp"

Life::Life(Game* arg_game)
{
	game = arg_game;
	menu = new(LifeMenu)(this,game);
}

void Life::init()
{
	int preset=1;
	resizeGrid(size.x,size.y);
	resizeGrid(10,30);
	m_oldGrid = m_grid;
	m_generation = 0;
	m_tick = 0;
	m_speed = 20;
	generatePreset(preset);
}

void Life::update()
{
	if (!m_frozen && !m_paused)
	{
		++m_tick;
		if (!(m_tick % m_speed))
		{
			nextGen();
		}
	}
}

void Life::render()
{
	bool alive = false;
	int w = 0;
		int h = 0;
		SDL_GetWindowSize(game->window,&w,&h);
		for (int i = 0 ; i<size.x ; ++i)
		{
			for (int j = 0 ; j<size.y ; ++j)
			{
				alive = getCell(i,j);
				SDL_Rect cell {(i*scale-i)+offset.x,(j*scale-j)+offset.y,scale,scale};
				SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
				if (alive)
				{
					SDL_RenderFillRect(game->renderer,&cell);
				}
				else if(!alive)
				{
					SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(game->renderer,&cell);
				}
				SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(game->renderer,&cell);
			}
		}
}

void Life::nextGen()
{
	// Update entire grid
	int neighbors = 0;
	int xp,xm,yp,ym = 0;
	m_oldGrid = m_grid;
	for (int x=0; x<size.x; ++x)
	{
		xp = (x+1)%size.x;
		xm = ((x-1) % size.x + size.x) % size.x;
		for (int y=0; y<size.y; ++y)
		{
			yp = (y+1)%size.y;
			ym = ((y-1) % size.y + size.y) % size.y;

			neighbors = m_oldGrid[xp][yp] + m_oldGrid[xm][ym] +
					m_oldGrid[xp][y] + m_oldGrid[x][yp] +
					m_oldGrid[xm][y] + m_oldGrid[x][ym] +
					m_oldGrid[xp][ym] + m_oldGrid[xm][yp];

			// If dead cell surrounded by 3 live, create life
			if (m_oldGrid[x][y] == false && neighbors == 3)
			{
				// std::cout << "Created life at [" << x << "][" << y << "]" << std::endl;
				m_grid[x][y] = true;
			}

			// Live cell stays alive if 3 or 2 neighbors
			else if ((neighbors == 3 || neighbors == 2) && m_oldGrid[x][y] == true)
			{

			}

			// The rest die
			else
			{
				m_grid[x][y] = false;
			}
		}
	}
	++m_generation;
}

void Life::pauseGame(bool paused)
{
	m_paused = paused;
}

void Life::freezeSimulation(bool frozen)
{
	m_frozen = frozen;
}

void Life::toggleFrozen()
{
	m_frozen = !m_frozen;
}

void Life::togglePause()
{
	m_paused = !m_paused;
}

void Life::resizeGrid(int x, int y)
{
	m_grid.resize(x);
	for (int i=0; i<x; ++i)
	{
		m_grid[i].resize(y,false);
	}
	size.x = x;
	size.y = y;
}

int Life::createGlider(int x, int y)
{
	m_grid[x][y] = true;
	m_grid[x][y-1] = true;
	m_grid[x][y-2] = true;
	m_grid[x-1][y] = true;
	m_grid[x-2][y-1] = true;

	return 0;
}

int Life::createBlinker(int x, int y)
{
	for (int i=0 ; i<3 ; ++i)
	{
		m_grid[x+i-1][y] = true;
	}

	return 0;
}

int Life::createPentaDecathlon(int x, int y)
{
	for (int i=0; i<10; ++i)
	{
		if (i == 2 || i == 7)
		{
			m_grid[x-1][y+i-4] = true;
			m_grid[x+1][y+i-4] = true;
		}
		else
		{
			m_grid[x][y+i-4] = true;
		}
	}

	return 0;
}

void Life::generatePreset(int preset)
{
	switch(preset)
	{
		case 1:
			createGlider(3,3);
			break;

		case 2:
			createPentaDecathlon(12,12);
			break;

		default:
			break;
	}
}

void Life::spaceAction()
{
	toggleFrozen();
}

void Life::enterAction()
{
	nextGen();
}

void Life::escapeAction()
{
	game->pushState(menu);
}

void Life::moveUpAction()
{
	offset.y += 4;
}

void Life::moveDownAction()
{
	offset.y -= 4;
}

void Life::moveLeftAction()
{
	offset.x += 4;
}

void Life::moveRightAction()
{
	offset.x -= 4;
}

void Life::zoomDownAction()
{
	if (scale >= 5)
	{
		--scale;
	}
}

void Life::zoomUpAction()
{
	if (scale <= 60)
	{
		++scale;
	}
}

bool Life::getCell(int x, int y)
{
	return m_grid[x][y];
}

int Life::getGen()
{
	return m_generation;
}

void Life::setSpeed(int ticksPerGen)
{
	m_speed = ticksPerGen;
}
