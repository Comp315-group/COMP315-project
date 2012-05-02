#include "MainMenu.h"
#include "GFX.h"

MainMenu::MainMenu()
{
    //Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.Top= 248;
	playButton.rect.Bottom = 475;
	playButton.rect.Left = 85;
	playButton.rect.Right = 940;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.Left = 85;
	exitButton.rect.Right = 945;
	exitButton.rect.Top = 532;
	exitButton.rect.Bottom = 702;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

    //custom cursor
	cursorImage = load_image("resource/img/cursor.png");
	cursor.SetImage(cursorImage);

    //To start with, cursor is positioned near the center of the window
    //it updates on the first instance of cursor movement
    cursor.SetX(500);
    cursor.SetY(400);
}

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    mAction = false;

    //Load menu image from file
	sf::Image image;
	image.LoadFromFile("resource/img/mainmenu.png");
	bgSprite.SetImage(image);
	window.Draw(bgSprite);
	window.Draw(cursor);
	window.Display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
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

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
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
