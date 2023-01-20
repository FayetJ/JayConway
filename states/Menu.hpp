#ifndef MENU_HPP
#define MENU_HPP

#include "GameState.hpp"

class Menu : public GameState
{
public:
	Menu();

	// Boilerplate
	void update();
	void render();
	void init();
	void cleanup(){};
	void pause(){};
	void resume(){};

	// Inputs
	void upAction();
	void downAction();
	void escapeAction();
	void moveUpAction(){};
	void moveDownAction(){};
	void moveLeftAction(){};
	void moveRightAction(){};
	void zoomUpAction(){};
	void zoomDownAction(){};
	void enterAction(){};
	void clear(){};

	void click(int x, int y){};

	// Menu Display
	virtual void renderBg(){};
	void displayEntry(int n, int x, int y, bool selected);
	void displayEntries();
	void displayNumber(int number, int x, int y, bool selected);
	void displayValue(int n, bool selected);

protected:
	TTF_Font *font = nullptr;
	SDL_Color color = SDL_Color{255,255,255};
	std::vector<SDL_Texture*> t_unselected;
	std::vector<SDL_Texture*> t_selected;
	std::array<SDL_Texture*,10> n_selected;
	std::array<SDL_Texture*,10> n_unselected;
	std::vector<std::string> a_texts;
	std::vector<int> values;
	std::array<std::string,10> a_numbers;
	Game* game = nullptr;
	SDL_Rect* fullscreenRect = nullptr;
	SDL_Rect* menuRect = nullptr;
	int scalex = 0;
	int scaley = 0;
	int tscalex = 0;
	int tscaley = 0;
	int selector = 0;
};

#endif // MENU_HPP
