#ifndef PLAYMENU_H_INCLUDED
#define PLAYMENU_H_INCLUDED

#include "MainMenu.h"

class PlayMenu : public MainMenu
{
    public:
        enum MenuResult { Nothing, Solo, Multi, Back, Exit };
        PlayMenu();
        MenuResult Show(sf::RenderWindow& window);

    struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult action;
		};

	private:
        std::list<MenuItem> _menuItems;
        MenuResult GetMenuResponse(sf::RenderWindow& window);
        PlayMenu::MenuResult HandleClick(int x, int y);
};


#endif // PLAYMENU_H_INCLUDED
