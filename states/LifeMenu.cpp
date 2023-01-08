#include "LifeMenu.hpp"
#include "Life.hpp"

LifeMenu::LifeMenu(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
	a_texts.resize(6);
	values.resize(6);
	std::fill(values.begin(), values.end(), -1);
	a_texts = {"Resume", "Speed", "Settings", "Exit game", "Pain", "Test"};
	settings = new LifeSettings(life,game);
}

void LifeMenu::renderBg()
{
	life->render();
}

void LifeMenu::enterAction()
{
	switch(selector)
	{
		case 2:
			game->pushState(settings);
			break;
	}
}
