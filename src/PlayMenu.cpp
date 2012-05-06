#include "PlayMenu.h"
#include "GFX.h"

PlayMenu::PlayMenu()
{
    MenuItem soloButton;
	soloButton.rect.Top= 248;
	soloButton.rect.Bottom = 475;
	soloButton.rect.Left = 85;
	soloButton.rect.Right = 940;
	soloButton.action = Solo;

	MenuItem multiButton;
	multiButton.rect.Left = 85;
	multiButton.rect.Right = 945;
	multiButton.rect.Top = 532;
	multiButton.rect.Bottom = 702;
	multiButton.action = Multi;

	MenuItem backButton;
	backButton.rect.Left=17;
	backButton.rect.Right=130;
	backButton.rect.Top=15;
	backButton.rect.Bottom=80;
	backButton.action = Back;

	_menuItems.push_back(soloButton);
	_menuItems.push_back(multiButton);
	_menuItems.push_back(backButton);

	 //custom cursor
	cursorImage = load_image("resource/img/cursor.png");
	cursor.SetImage(cursorImage);

    //To start with, cursor is positioned near the center of the window
    //it updates on the first instance of cursor movement
    cursor.SetX(400);
    cursor.SetY(350);

    mAction = false;
}

PlayMenu::MenuResult PlayMenu::Show(sf::RenderWindow& window)
{
    mAction = false;

    //Load menu image from file
	sf::Image image;
	image.LoadFromFile("resource/img/playmenu.png");
	bgSprite.SetImage(image);
	window.Draw(bgSprite);
	window.Draw(cursor);
	window.Display();

	return GetMenuResponse(window);
}

PlayMenu::MenuResult  PlayMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(42 != 43)
	{
		while(window.GetEvent(menuEvent))
		{
		    if (menuEvent.Type == sf::Event::MouseMoved)
		    {
		        int x = menuEvent.MouseMove.X;
		        int y = menuEvent.MouseMove.Y;

		        cursor.SetPosition(x, y);
		        window.Draw(bgSprite);
                window.Draw(cursor);
                window.Display();
		    }

			if(menuEvent.Type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
			}
			if(menuEvent.Type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}

PlayMenu::MenuResult PlayMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if( menuItemRect.Bottom > y
			&& menuItemRect.Top < y
			&& menuItemRect.Left < x
			&& menuItemRect.Right > x)
			{
				return (*it).action;
			}
	}

	return Nothing;
}

