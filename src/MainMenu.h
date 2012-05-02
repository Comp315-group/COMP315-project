#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED


#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>

class MainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play };
    MainMenu();
    void setMAction(bool b) {mAction = b;}
    bool tookMeaningfulAction() const {return mAction;}
	struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult action;
		};

	MenuResult Show(sf::RenderWindow& window);

private:
    //player clicked an appropriate button
    bool mAction;
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
	//custom cursor
	sf::Image cursorImage;
	sf::Sprite cursor;
	//menu sprite
	sf::Sprite bgSprite;
};

#endif // MAINMENU_H_INCLUDED
