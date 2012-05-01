#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include <string>

const int LETTER_WIDTH = 74;
const int LETTER_HEIGHT = 42;

const int PORTRAIT_X = 80;
const int PORTRAIT_Y = 156;

class PlayerMenu
{

public:
	enum MenuResult {
	    m1, m2, m3, m4, f1, f2, f3, f4, keyboard, play, nothing, exit
	    };
	PlayerMenu();
	bool isFinished() const {return finished;}
	bool hasAvatar() const {return choseAvatar;}
	void setChoseAvatar(bool b) {choseAvatar = b;}
	void setFinished(bool b) {finished = b;}
	std::string getName() const {return name;}
	void updatePortrait(sf::Image img);
	void updateName(char c);

	sf::Image getPortrait() const {return selectedPortraitImage;};

	struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult action;
			char letter;
		};

    MenuItem getClickedItem();
    MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	MenuItem clickedItem;
	//prevents the player from having no avatar/portrait
	bool choseAvatar;
	std::list<MenuItem> _menuItems;
	//player is finished creating character
	bool finished;
	//The menu image
	sf::Sprite image;
    //The string representation of the player's name
	std::string name;
	//The text containing the player's name
	sf::String nameText;
	//The selected portrait, stored as a pointer since it's display is dependant on whether or not a portrait has been selected
	sf::Sprite *selectedPortrait;
	//The image for the portrait sprite
	sf::Image selectedPortraitImage;

};
