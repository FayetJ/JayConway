#include "LifeMenu.hpp"
#include "Life.hpp"

LifeMenu::LifeMenu(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
	a_texts.resize(6);
	a_texts = {"Resume", "Speed", "Settings", "Exit game", "Pain", "Test"};
}

void LifeMenu::renderBg()
{
	life->render();
}
