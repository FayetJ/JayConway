#include "LifeSettings.hpp"
#include "LifeMenu.hpp"
#include "Life.hpp"

LifeSettings::LifeSettings(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
	a_texts.resize(3);
	values.resize(3);
	//values = {life->getSpeed(),life->getHeight(),life->getWidth()};
	values = {life->getSpeed(),life->getHeight(),life->getWidth()};
	a_texts = {"Ticks per update", "Height", "Width"};
}

void LifeSettings::renderBg()
{
	life->render();
}

void LifeSettings::testNumber()
{
	displayNumber(123,100,100,0);
}

void LifeSettings::rightAction()
{
	values[selector]++;
}

void LifeSettings::leftAction()
{
	values[selector]--;
}

void LifeSettings::escapeAction()
{
	life->setSpeed(values[0]);
	life->setHeight(values[1]);
	life->setWidth(values[2]);
	game->popState();
}
