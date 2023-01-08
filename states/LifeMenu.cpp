#include "LifeMenu.hpp"
#include "Life.hpp"

LifeMenu::LifeMenu(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
	a_texts.resize(3);
	values.resize(3);
	std::fill(values.begin(), values.end(), -1);
	a_texts = {"Resume", "Settings", "Exit game"};
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
		case 0:
			game->popState();
			break;

		case 1:
			game->pushState(settings);
			break;
		case 2:
			game->close();
	}
}
