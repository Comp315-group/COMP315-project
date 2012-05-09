#include "SplashScreen.h"


void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    //the image for the splash screen
	sf::Image image;
	if(image.LoadFromFile("resource/img/SplashScreen.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	renderWindow.Draw(sprite);
	renderWindow.Display();

	sf::Event event;
	//any action closes the splash screen
	while(true)
	{
		while(renderWindow.GetEvent(event))
		{
			if(event.Type == sf::Event::KeyPressed
				|| event.Type == sf::Event::MouseButtonPressed
				|| event.Type == sf::Event::Closed )
			{
				return;
			}
		}
	}
}
