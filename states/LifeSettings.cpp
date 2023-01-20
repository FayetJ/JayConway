#include "LifeSettings.hpp"
#include "LifeMenu.hpp"
#include "Life.hpp"

LifeSettings::LifeSettings(Life* arg_life, Game* arg_game)
{
	life = arg_life;
	game = arg_game;
	a_texts.resize(3);
	values.resize(3);
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
	if (values[selector] < 1000)
	{
		values[selector]++;
	}
}

void LifeSettings::leftAction()
{
	if(values[selector]>1)
	{
		values[selector]--;
	}
}

void LifeSettings::cleanup()
{
	life->setSpeed(values[0]);
	if (life->getHeight() != values[1] || life->getWidth() != values[2])
	{
		life->setHeight(values[1]);
		life->setWidth(values[2]);
	}
}
