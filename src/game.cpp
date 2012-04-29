#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.Create(sf::VideoMode(1024,768,32),"COMP315project",sf::Style::Close);
	//_mainWindow.SetFramerateLimit(60);  //Game runs at 30FPS maximum
	oddonegame = new OddOneGame();
	mazegame = new MazeGame();
	hidegame = new HideGame();
	matchinggame = new MatchingGame();
	srand(time(0));

	 player1 = new Player("lunch", load_image("resource/img/player.bmp")); //create player object

	_gameState= Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.Close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	switch(_gameState)
	{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case Game::Playing_maze:
			{
				sf::Event currentEvent;
                if (mazegame == NULL)
                    mazegame = new MazeGame();

				while(_mainWindow.GetEvent(currentEvent))
					{
                        _mainWindow.Clear(sf::Color(0,0,0));

                        mazegame->draw(_mainWindow);
                        _mainWindow.Draw(player1->getSprite());
                        _mainWindow.Display();

                        if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

                        if(currentEvent.Type == sf::Event::KeyPressed)
                            {
                                if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();

                                    else(mazegame->handle_input(player1, currentEvent));
                            }

                        if (mazegame->gameOver())
                        {
                                randomizeGameState();   //move to next game
                                mazegame = NULL;
                                break;
                        }
					}
				break;
			}
			case Game::Playing_odd:
			{
			   sf::Event currentEvent;
			   if (oddonegame == NULL)
                    oddonegame = new OddOneGame();

           while(_mainWindow.GetEvent(currentEvent))
					{
					_mainWindow.Clear(sf::Color(0,0,0));

                    oddonegame->draw(_mainWindow);
                    _mainWindow.Display();

					if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

					if(currentEvent.Type == sf::Event::KeyPressed)
						{
							if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
						}

                    if(currentEvent.Type == currentEvent.MouseButtonPressed  && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;

                        if((posx >= 10 && posx <= 1000) && (posy >= 250 && posy <= 500)){
                            oddonegame->correct(posx, posy);
                            oddonegame->drawText(_mainWindow); //draw correct String
                            //sf::Sleep(0.5f);

                            if(oddonegame->gameOver())
                            {
                                randomizeGameState();   //move to next game

                                oddonegame = NULL;
                                break;
                            }
                        }
                    }
                }

					 break;
			}

			case Game::Playing_hide:
			{

            sf::Event currentEvent;

            if (hidegame == NULL)
                hidegame = new HideGame();

            while(_mainWindow.GetEvent(currentEvent))
					{
					_mainWindow.Clear(sf::Color(0,0,0));

                    hidegame->draw(_mainWindow);


					if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

					if(currentEvent.Type == sf::Event::KeyPressed)
						{
							if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
						}

                    if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;


                       if((posx >= 125 && posx <= 875) && (posy >= 200 && posy <= 650)){
                           hidegame->correct(posx, posy);
                           hidegame->DrawText(_mainWindow);

                           if (hidegame->gameOver())
                           {
                               randomizeGameState();

                               hidegame = NULL;
                               break;
                           }

                        }

                    }
                    _mainWindow.Display();
					}
					break;
            }

            case Game::Playing_matching:
			{

            sf::Event currentEvent;
            if (matchinggame == NULL)
                matchinggame = new MatchingGame();
           while(_mainWindow.GetEvent(currentEvent))
					{
					_mainWindow.Clear(sf::Color(0,0,0));

                    matchinggame->draw(_mainWindow);


					if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

					if(currentEvent.Type == sf::Event::KeyPressed)
						{
							if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
						}

                    if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;


                       if((posx >= 40 && posx <= 980) && (posy >= 375 && posy <= 590)){
                            matchinggame->correct(posx, posy);
                            matchinggame->drawText(_mainWindow);

                            if (matchinggame->gameOver())
                           {
                               randomizeGameState();

                               matchinggame = NULL;
                               break;
                           }
                        }

                    }
                    _mainWindow.Display();
					}
					break;
            }

            case Game::Playing_pattern:
			{
            sf::Event currentEvent;
            if (patterngame == NULL)
                patterngame = new PatternGame();
           while(_mainWindow.GetEvent(currentEvent))
					{
					_mainWindow.Clear(sf::Color(0,0,0));

                    patterngame->draw(_mainWindow);


					if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

					if(currentEvent.Type == sf::Event::KeyPressed)
						{
							if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
						}

                    if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;

                       if((posx >= 190 && posx <= 810) && (posy >= 400 && posy <= 600)){
                            patterngame->correct(posx, posy);
                            patterngame->drawText(_mainWindow);

                            if (patterngame->gameOver())
                           {
                               randomizeGameState();

                               patterngame = NULL;
                               break;
                           }
                        }

                    }
                    _mainWindow.Display();
					}
					break;
            }
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing_maze;
			break;
	}
}

void Game::randomizeGameState()
{
    int random = rand() % 5;

    switch (random)
    {
        case 0:
        _gameState = Playing_maze;
        break;
        case 1:
        _gameState = Playing_hide;
        break;
        case 2:
        _gameState = Playing_matching;
        break;
        case 3:
        _gameState = Playing_odd;
        break;
        case 4:
        _gameState = Playing_pattern;
        break;

    }
}

int main()
{
    Game::Start();

    return 0;
}
