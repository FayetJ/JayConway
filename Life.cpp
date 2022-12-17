#include "Life.hpp"

Life::Life()
{

}

Life::~Life()
{
	m_running = false;
}

void Life::init(int preset)
{
	m_grid[0].fill(false);
	m_grid.fill(m_grid[0]);
	m_oldGrid = m_grid;
	m_generation = 0;
	m_tick = 0;
	m_running = true;
	m_speed = 10;
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

void Life::nextGen()
{
	// Update entire grid
	int neighbors = 0;
	int xp,xm,yp,ym = 0;
	m_oldGrid = m_grid;
	for (int x=0; x<arraySize; ++x)
	{
		xp = (x+1)%arraySize;
		xm = ((x-1) % arraySize + arraySize) % arraySize;
		for (int y=0; y<arraySize; ++y)
		{
			yp = (y+1)%arraySize;
			ym = ((y-1) % arraySize + arraySize) % arraySize;

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
	m_running = !m_running;
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

bool Life::getCell(int x, int y)
{
	return m_grid[x][y];
}

int Life::getSize()
{
	return arraySize;
}

int Life::getGen()
{
	return m_generation;
}

void Life::setSpeed(int ticksPerGen)
{
	m_speed = ticksPerGen;
}
