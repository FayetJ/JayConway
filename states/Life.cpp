#include "Life.hpp"

Life::Life(Game* arg_game)
{
	game = arg_game;
}

void Life::init()
{
	int preset=0;
	resizeGrid(size.x,size.y);
	resizeGrid(50,50);
	m_oldGrid = m_grid;
	m_generation = 0;
	m_tick = 0;
	m_speed = 10;
	generatePreset(preset);
	menu = new(LifeMenu)(this,game);
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
	if (!renderInfinity)
	{
		renderGrid();
	}
	// Render Infinity : Experimental feature allowing for infinite grid rendering
	else if (renderInfinity)
	{
		int iterations = 1;
		if (iterations==0)
		{
			renderGrid();
		}
		else
		{
			for (int i=-iterations; i<=iterations; ++i)
			{
				for(int j=0; j<=iterations; ++j)
				{
					//renderGrid(-j*((scale-1)*size.x+1),i*((scale-1)*size.y+1));
					//renderGrid(j*((scale-1)*size.x+1),i*((scale-1)*size.y+1));
				}
			}
		}
	}
}

void Life::renderGrid()
{
	bool alive = false;
	int lineOffset = 0;
	cell.h = scale;
	cell.w = scale;
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(game->renderer, offset.x, lineOffset + offset.y, offset.x + (scale-1)*size.x, lineOffset+offset.y);
	SDL_RenderDrawLine(game->renderer, lineOffset + offset.x, offset.y, lineOffset + offset.x, (offset.y) + (scale-1) * size.y);
	for (int i = 0 ; i<size.x ; ++i)
	{
		lineOffset = lineOffset + scale - 1;
		for (int j = 0 ; j<size.y ; ++j)
		{
			alive = getCell(i,j);
			if (alive)
			{
				cell.x = (i*scale-i)+offset.x;
				cell.y = (j*scale-j)+offset.y;
				SDL_RenderFillRect(game->renderer,&cell);
			}
		}
		SDL_RenderDrawLine(game->renderer, lineOffset + offset.x, offset.y, lineOffset + offset.x, (offset.y) + (scale-1) * size.y);
	}
	lineOffset = 0;
	for (int i = 0 ; i<size.y ; ++i)
	{
		lineOffset = lineOffset + scale - 1;
		SDL_RenderDrawLine(game->renderer, offset.x, lineOffset + offset.y, offset.x + (scale-1)*size.x, lineOffset+offset.y);
	}
}

void Life::nextGen()
{
	// Creates next generation of the grid
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
	clearGrid();
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
		case 0:
			break;
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

void Life::delAction()
{
	clearGrid();
}

void Life::click(int x, int y)
{
	getIndex(&x,&y);
	swapCell(x,y);
}

void Life::clearGrid()
{
	for (int i=0; i<m_grid.size(); ++i)
	{
		for (int j=0; j<m_grid[0].size(); ++j)
		{
			m_grid[i][j] = false;
		}
	}
}

void Life::getIndex(int *x, int *y)
{
	*x = int((*x - offset.x)/(scale-1));
	*y = int((*y - offset.y)/(scale-1));
}

void Life::swapCell(int x, int y)
{
	if ((y < m_grid[0].size() && y>=0) && (x < m_grid.size() && x>=0) )
	{
		m_grid[x][y] = !m_grid[x][y];
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

void Life::setHeight(int height)
{
	resizeGrid(size.x,height);
}

void Life::setWidth(int width)
{
	resizeGrid(width,size.y);
}

int Life::getSpeed()
{
	return m_speed;
}

int Life::getHeight()
{
	return size.y;
}

int Life::getWidth()
{
	return size.x;
}
