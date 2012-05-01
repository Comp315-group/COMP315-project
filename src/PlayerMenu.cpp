#include "PlayerMenu.h"

PlayerMenu::MenuResult  PlayerMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(42 != 43)
	{

		while(window.GetEvent(menuEvent))
		{
		    if (menuEvent.Type == sf::Event::Closed)
                return exit;

			if(menuEvent.Type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
			}
		}
	}
}

void PlayerMenu::updatePortrait(sf::Image img)
{
    selectedPortraitImage = img;
    selectedPortrait = new sf::Sprite(selectedPortraitImage);
    selectedPortrait->SetPosition(PORTRAIT_X, PORTRAIT_Y);
}

void PlayerMenu::updateName(char c)
{
    //maximum name size of 15 characters
    if (name.size() < 15 || c == '*')
    {
        //backspace was pressed
        if (c == '*')
        {
            //name is already empty
            if (name.size() == 0)
                return;

            name = name.substr(0, name.size()-1);
            nameText.SetText(name);
            return;
        }
        name += c;
        nameText.SetText(name);
    }
}

PlayerMenu::MenuResult PlayerMenu::HandleClick(int x, int y)
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
			    clickedItem = *it;
				return (*it).action;
			}
	}

	return nothing;
}

PlayerMenu::MenuItem PlayerMenu::getClickedItem()
{
    return clickedItem;
}

PlayerMenu::PlayerMenu()
{
    finished = false;
    choseAvatar = false;
    name = "PLAYER";
    nameText.SetPosition(482, 515);
    nameText.SetColor(sf::Color::Cyan);
    nameText.SetText(name);

    selectedPortrait = NULL;
}

PlayerMenu::MenuResult PlayerMenu::Show(sf::RenderWindow& window)
{

     //Load menu image from file
	sf::Image img;
	img.LoadFromFile("resource/img/Playermenu.png");
	image.SetImage(img);

	//Setup clickable regions

	////////////////////
	////////////////////
	/////PORTRAITS//////
	////////////////////
	////////////////////

    //male portraits
	MenuItem M1;
	M1.rect.Top = 120;
	M1.rect.Bottom = 216;
	M1.rect.Left = 374;
	M1.rect.Right = 468;
	M1.action = m1;

	_menuItems.push_back(M1);

	MenuItem M2;
	M2.rect.Top = 120;
	M2.rect.Bottom = 216;
	M2.rect.Left = 526;
	M2.rect.Right = 623;
	M2.action = m2;

	_menuItems.push_back(M2);

	MenuItem M3;
	M3.rect.Top = 120;
	M3.rect.Bottom = 216;
	M3.rect.Left = 668;
	M3.rect.Right = 764;
	M3.action = m3;

	_menuItems.push_back(M3);

	MenuItem M4;
	M4.rect.Top = 120;
	M4.rect.Bottom = 216;
	M4.rect.Left = 823;
	M4.rect.Right = 918;
	M4.action = m4;

	_menuItems.push_back(M4);

	//female portraits
	MenuItem F1;
	F1.rect.Top = 265;
	F1.rect.Bottom = 362;
	F1.rect.Left = 372;
	F1.rect.Right = 469;
	F1.action = f1;

	_menuItems.push_back(F1);

    MenuItem F2;
	F2.rect.Top = 265;
	F2.rect.Bottom = 362;
	F2.rect.Left = 525;
	F2.rect.Right = 621;
	F2.action = f2;

	_menuItems.push_back(F2);

	MenuItem F3;
	F3.rect.Top = 265;
	F3.rect.Bottom = 362;
	F3.rect.Left = 670;
	F3.rect.Right = 765;
	F3.action = f3;

	_menuItems.push_back(F3);

	MenuItem F4;
	F4.rect.Top = 265;
	F4.rect.Bottom = 362;
	F4.rect.Left = 822;
	F4.rect.Right = 919;
	F4.action = f4;

	_menuItems.push_back(F4);


    ///////////////////
	///////////////////
	/////KEYBOARD//////
	///////////////////
	///////////////////

	//For the on-screen keyboard, only the coordinates of "a" are specified. The rest are determined dynamically
	int farLeft = 177;
	int top = 579;
	int row = 0;
	int col = 1;

	MenuItem a;
	a.rect.Top = top;
	a.rect.Bottom = top + LETTER_HEIGHT;
	a.rect.Left = farLeft;
	a.rect.Right = farLeft + LETTER_WIDTH;
	a.action = keyboard;
	a.letter = 'A';

    _menuItems.push_back(a);

	for (int i = 1; i < 25; i++)
	{
	    if (col == 8)
	    {
	        col = 0;
	        row++;
	    }

	    MenuItem temp;
	    temp.rect.Top = top + (row*LETTER_HEIGHT);
	    temp.rect.Bottom = temp.rect.Top + LETTER_HEIGHT;
	    temp.rect.Left = farLeft + (col*LETTER_WIDTH);
	    temp.rect.Right = temp.rect.Left + LETTER_WIDTH;
	    temp.action = keyboard;
	    temp.letter = a.letter + i;

	    _menuItems.push_back(temp);

	    col++;
	}

	MenuItem space;
	space.rect.Top = 705;
	space.rect.Bottom = 747;
	space.rect.Left = 328;
	space.rect.Right = 632;
	space.action = keyboard;
	space.letter = ' ';

    _menuItems.push_back(space);

    MenuItem back;
	back.rect.Top = 705;
	back.rect.Bottom = 747;
	back.rect.Left = 632;
	back.rect.Right = 707;
	back.action = keyboard;
	back.letter = '*';

    _menuItems.push_back(back);

    //play button
    MenuItem playItem;
    playItem.rect.Top = 628;
    playItem.rect.Bottom = 730;
    playItem.rect.Left = 838;
    playItem.rect.Right = 991;
    playItem.action = play;

    _menuItems.push_back(playItem);

    ///////////////////
	///////////////////
	//////DRAWING//////
	///////////////////
	///////////////////

	window.Draw(image);

    if (selectedPortrait != NULL)
        window.Draw(*selectedPortrait);

	window.Draw(nameText);
	window.Display();

	return GetMenuResponse(window);
}
