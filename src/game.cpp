/**
    The game class is responsible for displaying the splash screen, main menu and game window
    It controls the flow of the game and passes parameters to individual game classes for
    key game events like drawing, handling of input etc.
*/

////////////////////////
////////INCLUDES////////
////////////////////////

#include "Game.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "SplashScreen.h"
#include <time.h>
#include <iostream> //TODO: remove this

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
Game::GameState Game::tempGameState;
sf::RenderWindow Game::_mainWindow;

/*
    Starts the game by initialising all key variables and all player classes
    Thereafter it runs the Game Loop.
*/

void Game::Start(void)
{
    if(_gameState != Uninitialized)
        return;

    //Main display window initialised to 1024x768 and 32bit colour-depth
    _mainWindow.Create(sf::VideoMode(1024,768,32),"EduGame",sf::Style::Close);

    //Custom cursor is drawn in place of the default cursor
    _mainWindow.ShowMouseCursor(false);

    //Custom window icon
    sf::Image icon = load_image("resource/img/icon.png");
    _mainWindow.SetIcon(32, 32, icon.GetPixelsPtr());

    //create player object(s)
    player1 = new Player("lunch", load_image("resource/img/player.bmp"));

    ip = sf::IPAddress::GetLocalAddress();

    //load the image for the mouse cursor
    sf::Image mouseImg = load_image("resource/img/cursor.png");
    cursor.SetImage(mouseImg);

    //load background image and initialise corresponding sprite
    bgImage = load_image("resource/img/bg.jpg");
    bgSprite.SetImage(bgImage);
    bgSprite.SetX(0);
    bgSprite.SetY(0);

    //load end-game image and initialise corresponding sprite
    gameOverImage = load_image("resource/img/gameover.jpg");
    gameOverSprite.SetImage(gameOverImage);
    gameOverSprite.SetX(0);
    gameOverSprite.SetY(0);

    //initialise all game instance classes. Each class is responsible for its own logic
    oddonegame = new OddOneGame();
    hidegame = new HideGame();
    matchinggame = new MatchingGame();
    wordfilgame = new WordfillGame();
    mazegame = NULL;
    pickupgame = NULL;

    //seed RNG
    srand(time(0));

    //initialise the sound manager
    sound_manager.init();

    //initialise the text that notifies the player about their score
    score_text.SetText("Score : " + toString(player1->getScore()));
    score_text.SetSize(20);
    score_text.SetColor(sf::Color ::Green);
    score_text.SetPosition(0,0);

    //show the splash screen
    _gameState= Game::ShowingSplash;

    //run the game loop until the game is ready to exit
    while(!IsExiting())
    {
        GameLoop();
    }

    //close window, exit game
    _mainWindow.Close();
}

/*
    Returns whether or not the game is in the Exiting state
*/

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

/*
    The game loop controls the flow of the game by drawing game components to screen, parsing player input and determining
    whether or not games have been successfully completed
*/

void Game::GameLoop()
{
    switch(_gameState)
    {
        //game menu is currently being displayed
    case Game::ShowingMenu:
    {
        ShowMenu();
        break;
    }

//shows the meun for playing the game
    case Game::ShowingPlayMenu:
    {
        ShowPlayMenu();
        break;
    }

    //splash menu is currently being displayed
    case Game::ShowingSplash:
    {
        ShowSplashScreen();
        break;
    }

    //Player creation is taking place
    case Game::Creating_Player:
    {
        ShowPlayerCreationScreen();
        break;
    }

    //maze game is currently being played
    case Game::Playing_maze:
    {
        //the event handler for this game
        sf::Event currentEvent;
        //on the second occurence of a maze game, the mazegame object will have been set to null
        //it is reinitialised here
        if (mazegame == NULL)
        {
            mazegame = new MazeGame();
            //reset player position
            mazegame->setPlayerStartLocation(player1);
        }

        //poll main window for event
        while(_mainWindow.GetEvent(currentEvent))
        {
            //clear screen and draw background followed by the maze followed by the player
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            mazegame->draw(_mainWindow);
            _mainWindow.Draw(player1->getSprite());

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //update the main window
            _mainWindow.Display();

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            //close button was clicked
            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            //key was pressed
            if(currentEvent.Type == sf::Event::KeyPressed)
            {

                //escape key pressed
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    //save game state in case player resumes
                    tempGameState = _gameState;
                    //set game state to paused
                    _gameState = Paused;
                    //show menu
                    ShowMenu();
                }

                //pass pressed key parameter to the mazegame class
                else
                {
                    mazegame->handle_input(player1, currentEvent);
                }
            }

            //player finished the maze
            if (mazegame->gameOver())
            {
                //play appropriate sound
                sound_manager.playCorrectSound();
                score_text.SetColor(sf::Color::Green);

                //award points to player
                player1->incrementScore(20);

                player1->incrementTime(_timekeeper.getTimeRemaining());

                //move to next game
                randomizeGameState(_gameState);

                //mazegame object is set to NULL so that it can be re-initialised if we need to create another
                //mazegame object
                mazegame = NULL;
                break;
            }
        }
        break;
    }

    //playing pickup game
    case Game::Playing_pickup:
    {
        //the event handler for this game
        sf::Event currentEvent;
        //on the second occurence of a maze game, the mazegame object will have been set to null
        //it is reinitialised here
        if (pickupgame == NULL)
        {
            pickupgame = new PickupGame();
            //reset player position
            pickupgame->setPlayerStartLocation(player1);
        }

        //poll main window for event
        while(_mainWindow.GetEvent(currentEvent))
        {
            //clear screen and draw background followed by the maze followed by the player
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            pickupgame->draw(_mainWindow);
            _mainWindow.Draw(player1->getSprite());

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //update the main window
            _mainWindow.Display();

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            //close button was clicked
            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            //key was pressed
            if(currentEvent.Type == sf::Event::KeyPressed)
            {

                //escape key pressed
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    //save game state in case player resumes
                    tempGameState = _gameState;
                    //set game state to paused
                    _gameState = Paused;
                    //show menu
                    ShowMenu();
                }

                //pass pressed key parameter to the mazegame class
                else
                {
                    pickupgame->handle_input(player1, currentEvent);
                }
            }

            //player finished the pickupgame
            if (pickupgame->pickUpGameOver())
            {
                //play appropriate sound
                sound_manager.playCorrectSound();
                score_text.SetColor(sf::Color::Green);

                //award points to player
                player1->incrementScore(50);


                player1->incrementTime(_timekeeper.getTimeRemaining());
                //move to next game
                randomizeGameState(_gameState);

                //pickup object is set to NULL so that it can be re-initialised if we need to create another
                //pickupgame object
                pickupgame = NULL;
                break;
            }
        }
        break;
    }

    //odd one out  game is currently being played
    case Game::Playing_odd:
    {
        //the event handler for this game
        sf::Event currentEvent;

        //on the second occurence of an odd-one-out game, the odd-one-out object will have been set to null
        //it is reinitialised here
        if (oddonegame == NULL)
            oddonegame = new OddOneGame();

        //poll main window for event
        while(_mainWindow.GetEvent(currentEvent))
        {
            //clear screen and draw background followed by the odd-one-out game's components
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            oddonegame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //update main window
            _mainWindow.Display();

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            //close button was clicked
            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            //escape key pressed
            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    //save game state in case player resumes
                    tempGameState = _gameState;
                    //set game state to paused
                    _gameState = Paused;
                    //show menu
                    ShowMenu();
                }
            }

            //left mouse button was clicked
            if(currentEvent.Type == currentEvent.MouseButtonPressed  && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                //get click coordinates
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;

                if((posx >= 10 && posx <= 1000) && (posy >= 250 && posy <= 500))
                {
                    oddonegame->correct(posx, posy);
                    oddonegame->drawText(_mainWindow);

                    if(oddonegame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(10);


                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);   //move to next game
                        oddonegame = NULL;
                        break;
                    }

                    else
                    {
                        sound_manager.playIncorrectSound();
                        score_text.SetColor(sf::Color::Red);
                        player1->incrementScore(-5);

                    }
                }
            }
        }

        break;
    }

    //Hide game is currently being played
    case Game::Playing_hide:
    {
//the event handler for this game
        sf::Event currentEvent;

        //on the second occurence of an Hide game, the Hide object will have been set to null
        //it is reinitialised here
        if (hidegame == NULL)
            hidegame = new HideGame();

        //poll main window for event
        while(_mainWindow.GetEvent(currentEvent))
        {
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            hidegame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

//close button was clicked
            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;
//escape key pressed
            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    tempGameState = _gameState;
                    _gameState = Paused;
                    ShowMenu();
                }
            }
            //left mouse button was clicked

            if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;


                if((posx >= 125 && posx <= 875) && (posy >= 200 && posy <= 650))
                {
                    hidegame->correct(posx, posy);
                    hidegame->DrawText(_mainWindow);

                    if (hidegame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(10);


                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);
                        hidegame = NULL;
                        break;
                    }

                    else
                    {
                        sound_manager.playIncorrectSound();
                        score_text.SetColor(sf::Color::Red);
                        player1->incrementScore(-5);

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
            _mainWindow.Draw(bgSprite);
            matchinggame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    tempGameState = _gameState;
                    _gameState = Paused;
                    ShowMenu();
                }
            }

            if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;


                if((posx >= 40 && posx <= 980) && (posy >= 375 && posy <= 590))
                {
                    matchinggame->correct(posx, posy);
                    matchinggame->drawText(_mainWindow);

                    if (matchinggame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(40);

                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);
                        matchinggame = NULL;
                        break;
                    }

                    else
                    {
                        sound_manager.playIncorrectSound();
                        score_text.SetColor(sf::Color::Red);
                        player1->incrementScore(-5);

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
            _mainWindow.Draw(bgSprite);
            patterngame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    tempGameState = _gameState;
                    _gameState = Paused;
                    ShowMenu();
                }
            }

            if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;

                if((posx >= 190 && posx <= 810) && (posy >= 400 && posy <= 600))
                {
                    patterngame->correct(posx, posy);
                    patterngame->drawText(_mainWindow);

                    if (patterngame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(10);


                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);
                        patterngame = NULL;
                        break;
                    }

                    else
                    {
                        sound_manager.playIncorrectSound();
                        score_text.SetColor(sf::Color::Red);
                        player1->incrementScore(-5);

                    }
                }

            }
            _mainWindow.Display();
        }
        break;
    }

    case Game::Playing_wordfill:
    {
        sf::Event currentEvent;
        if (wordfilgame == NULL)
            wordfilgame = new WordfillGame();

        while(_mainWindow.GetEvent(currentEvent))
        {
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            wordfilgame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            _mainWindow.Display();

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    tempGameState = _gameState;
                    _gameState = Paused;
                    ShowMenu();
                }
            }

            if(currentEvent.Type == currentEvent.MouseButtonPressed  && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;

                if((posx >= 320 && posx <= 720) && (posy >= 400 && posy <= 600))
                {

                    wordfilgame->correct(posx, posy);

                    if(wordfilgame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(10);


                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);   //move to next game
                        wordfilgame = NULL;
                        break;
                    }

                    else
                    {
                        sound_manager.playIncorrectSound();
                        score_text.SetColor(sf::Color::Red);
                        player1->incrementScore(-5);

                        _mainWindow.Display();
                    }
                }
            }
        }
        break;
    }

    case Game::Playing_wordsearch:
    {
        sf::Event currentEvent;
        if (wordsearchgame == NULL)
            wordsearchgame = new WordSearchGame();
        while(_mainWindow.GetEvent(currentEvent))
        {
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            wordsearchgame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    tempGameState = _gameState;
                    _gameState = Paused;
                    ShowMenu();
                }
            }

            if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;

                if((posx >= 400 && posx <= 625) && (posy >= 300 && posy <= 525))
                {
                    wordsearchgame->update(posx, posy);
                    wordsearchgame->drawText(_mainWindow);

                    if (wordsearchgame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(15);


                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);

                        wordsearchgame = NULL;
                        break;
                    }

                }
            }
            _mainWindow.Display();
        }
        break;
    }

    case Game::Playing_memory:
    {
        sf::Event currentEvent;
        if (memorygame == NULL)
            memorygame = new MemoryGame();

        while(_mainWindow.GetEvent(currentEvent))
        {
            _mainWindow.Clear(sf::Color(0,0,0));
            _mainWindow.Draw(bgSprite);
            memorygame->draw(_mainWindow);

            //Update and draw player score to screen
            score_text.SetText("Score : " + toString(player1->getScore()));
            _mainWindow.Draw(score_text);
            _mainWindow.Draw(cursor);

            //mouse was moved, move custom cursor
            if (currentEvent.Type == sf::Event::MouseMoved)
            {
                int x = currentEvent.MouseMove.X;
                int y = currentEvent.MouseMove.Y;

                cursor.SetPosition(x, y);
            }

            if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

            if(currentEvent.Type == sf::Event::KeyPressed)
            {
                if(currentEvent.Key.Code == sf::Key::Escape)
                {
                    tempGameState = _gameState;
                    _gameState = Paused;
                    ShowMenu();
                }
            }

            if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left)
            {
                int posx = currentEvent.MouseButton.X;
                int posy = currentEvent.MouseButton.Y;

                if((posx >= 375 && posx <= 675) && (posy >= 275 && posy <= 575))
                {
                    memorygame->update(posx, posy, _mainWindow);
                    _mainWindow.Draw(cursor);

                    if (memorygame->gameOver())
                    {
                        sound_manager.playCorrectSound();
                        score_text.SetColor(sf::Color::Green);
                        player1->incrementScore(50);

                        player1->incrementTime(_timekeeper.getTimeRemaining());
                        randomizeGameState(_gameState);

                        memorygame = NULL;
                        break;
                    }
                }
            }
            _mainWindow.Display();
        }
        break;
    }

//a player has won the game with 400 score
    case Game::Game_over:
    {
        if (solo)
        {
            //this event object is used to allow the player to press a key to leave the end-game screen
            sf::Event currentEvent;

            //reset player score
            player1->resetScore();

            //poll window for events
            while(_mainWindow.GetEvent(currentEvent))
            {
                //clear window, draw the game over image
                _mainWindow.Clear(sf::Color(0, 0, 0));
                _mainWindow.Draw(gameOverSprite);
                _mainWindow.Draw(player1->getAvatar());
                sf::String nameText;
                nameText.SetX(435);
                nameText.SetY(275);
                nameText.SetText(player1->getName());
                nameText.SetColor(sf::Color::Red);
                _mainWindow.Draw(nameText);
                score_text.SetPosition(435, 300);
                _mainWindow.Draw(score_text);
                _mainWindow.Draw(cursor);
                _mainWindow.Display();

                //mouse was moved, move custom cursor
                if (currentEvent.Type == sf::Event::MouseMoved)
                {
                    int x = currentEvent.MouseMove.X;
                    int y = currentEvent.MouseMove.Y;

                    cursor.SetPosition(x, y);
                }

                //close button clicked
                if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

                //key pressed
                if(currentEvent.Type == sf::Event::KeyPressed)
                {
                    //game returns to the menu
                    _gameState = ShowingMenu;
                    first_run = true;
                }
            }
            break;
        }


        else
        {
            //this event object is used to allow the player to press a key to leave the end-game screen
            sf::Event currentEvent;
            //reset player score
            player1->resetScore();
            player1->resetTime();

            sf::Packet winnerPacket;


            string name;
            unsigned short port = 9999;
            sf::IPAddress address(serverIP);

            if (clientSock.IsValid())
            {
                clientSock.SetBlocking(true);
                if (clientSock.Receive(winnerPacket, address, port) == sf::Socket::Done)
                {
                    winnerPacket >> name;
                    clientSock.Close();
                }
            }

            //poll window for events
            while(_mainWindow.GetEvent(currentEvent))
            {
                //clear window, draw the game over image
                _mainWindow.Clear(sf::Color(0, 0, 0));
                _mainWindow.Draw(gameOverSprite);

                sf::String nameText(name + " is the winner!");
                nameText.SetSize(75);
                nameText.SetPosition(400,400);
                nameText.SetText(player1->getName());
                nameText.SetColor(sf::Color::Red);
                _mainWindow.Draw(nameText);
                _mainWindow.Draw(cursor);
                _mainWindow.Display();

                //mouse was moved, move custom cursor
                if (currentEvent.Type == sf::Event::MouseMoved)
                {
                    int x = currentEvent.MouseMove.X;
                    int y = currentEvent.MouseMove.Y;

                    cursor.SetPosition(x, y);
                }

                //close button clicked
                if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

                //key pressed
                if(currentEvent.Type == sf::Event::KeyPressed)
                {
                    if(currentEvent.Key.Code == sf::Key::Return)
                    {
                        //game returns to the menu
                        _gameState = ShowingMenu;
                        first_run = true;
                    }
                }
            }
            break;
        }
    }
    }
    //Win condition has been met (singlePlayer)
    if (solo)
    {
        if (player1->getScore() >= 400)
        {
            //stop main music
            sound_manager.stopBGMusic();
            //play appropriate game over sound
            sound_manager.playGameOverSound();

            //set game state to indicate that the game is over
            _gameState = Game_over;
        }
    }

    else
        //Win condition has been met(multiPlayer
        if (clientSock.IsValid())
        {
            sf::Packet ggPacket;
            unsigned short port = 9999;
            sf::IPAddress server(serverIP);
            if (clientSock.Receive(ggPacket, server , port) == sf::Socket::Done)
            {
                string gg;
                ggPacket >> gg;

                if (gg == "GG")
                {
                    cout << "Recieved gg from server" << endl;
                    //send this player's information to the server for position calculation
                    sf::Packet infoPacket;
                    infoPacket << player1->getName();
                    infoPacket << player1->getScore();

                    if (clientSock.Send(infoPacket, server , port) == sf::Socket::Done)
                    {
                        cout << "Sent info packet to server" << endl;
                        //stop main music
                        sound_manager.stopBGMusic();
                        //play appropriate game over sound
                        sound_manager.playGameOverSound();

                        //set game state to indicate that the game is over
                        _gameState = Game_over;
                    }
                }
            }
        }
}

/*
    Create a SplashScreen object, display it and change the gamestate
*/
void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

/*
    Create a MainMenu object and determine which menu item the player clicked on
*/
void Game::ShowMenu()
{
    //create main menu
    MainMenu mainMenu;

    if (first_run)
    {
        //start playing background music if the menu is shown for the first time
        sound_manager.playBGMusic();
        first_run = false;
    }

    //get result
    while (!mainMenu.tookMeaningfulAction())
    {
        MainMenu::MenuResult result = mainMenu.Show(_mainWindow);

        switch(result)
        {
            //exit was clicked
        case MainMenu::Exit:
            mainMenu.setMAction(true);
            _gameState = Game::Exiting;
            break;
            //play was clicked
        case MainMenu::Play:
            mainMenu.setMAction(true);
            //if the player paused the game before, this resumes the game
            if (_gameState == Paused)
                _gameState = tempGameState;

            //Move to play menu
            else
            {
                //hack for now to fix a bug
                score_text.SetX(0);
                score_text.SetY(0);
                _gameState = Creating_Player;
            }
            break;
        }
    }
}

void Game::ShowPlayMenu()
{
    //create main menu
    PlayMenu playMenu;
    //get result
    while (!playMenu.tookMeaningfulAction())
    {
        PlayMenu::MenuResult result = playMenu.Show(_mainWindow);

        switch(result)
        {
            //solo was clicked
        case PlayMenu::Solo:
            playMenu.setMAction(true);
            solo = true;
            _timekeeper.start();
            randomizeGameState(_gameState);
            break;
            //multi was clicked
        case PlayMenu::Multi:
            playMenu.setMAction(true);
            ScanForServer();
            solo = false;
            //TODO: multi
            break;

            //back to main menu
        case PlayMenu::Back:
            playMenu.setMAction(true);
            _gameState = ShowingMenu;
            break;

            //exit was clicked
        case PlayMenu::Exit:
            playMenu.setMAction(true);
            _gameState = Game::Exiting;
            break;
        }
    }
}

/*
    Randomly determines what the next game to be played is. Ensures that the same game is never played
    twice in a row
*/
void Game::randomizeGameState(Game::GameState currentState)
{
    int random = rand() % 9;

    int cur = 0;
    switch(currentState)
    {
    case Playing_maze:
        cur = 0;
        break;

    case Playing_hide:
        cur = 1;
        break;

    case Playing_matching:
        cur = 2;
        break;

    case Playing_odd:
        cur = 3;
        break;

    case Playing_pattern:
        cur = 4;
        break;

    case Playing_wordfill:
        cur = 5;
        break;

    case Playing_memory:
        cur = 6;
        break;

    case Playing_wordsearch:
        cur = 7;
        break;
    case Playing_pickup:
        cur = 8;
        break;
    default:
        cur = 0;
        break;
    }

    //ensures that the same game can never be played twice in a row
    while (random == cur)
        random = rand() % 9;

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
    case 5:
        _gameState = Playing_wordfill;
        break;
    case 6:
        _gameState = Playing_memory;
        break;
    case 7:
        _gameState = Playing_wordsearch;
        break;
    case 8:
        _gameState = Playing_pickup;
        break;
    default:
        _gameState = Playing_maze;
        break;
    }
}

void Game::ShowPlayerCreationScreen()
{
    PlayerMenu plMenu;

    while (!plMenu.isFinished())
    {
        //get result
        PlayerMenu::MenuResult result = plMenu.Show(_mainWindow);
        sf::Image tempImg;

        switch(result)
        {
            //player clicked exit
        case PlayerMenu::exit:
            plMenu.setFinished(true);
            _gameState = Exiting;
            break;


        case PlayerMenu::play:
            if (!plMenu.hasAvatar() || plMenu.getName() == "")
                return;

            player1->setName(plMenu.getName());
            player1->changeAvatar(plMenu.getPortrait());

            plMenu.setFinished(true);
            //start mini-games
            _gameState = ShowingPlayMenu;

        case PlayerMenu::keyboard:
            plMenu.updateName(plMenu.getClickedItem().letter);
            break;

        case PlayerMenu::m1:
            tempImg = load_image("resource/img/avatar/m1.png");
            plMenu.setChoseAvatar(true);
            plMenu.updatePortrait(tempImg);
            break;

        case PlayerMenu::m2:
            tempImg = load_image("resource/img/avatar/m2.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;

        case PlayerMenu::m3:
            tempImg = load_image("resource/img/avatar/m3.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;

        case PlayerMenu::m4:
            tempImg = load_image("resource/img/avatar/m4.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;

        case PlayerMenu::f1:
            tempImg = load_image("resource/img/avatar/f1.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;

        case PlayerMenu::f2:
            tempImg = load_image("resource/img/avatar/f2.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;

        case PlayerMenu::f3:
            tempImg = load_image("resource/img/avatar/f3.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;

        case PlayerMenu::f4:
            tempImg = load_image("resource/img/avatar/f4.png");
            plMenu.updatePortrait(tempImg);
            plMenu.setChoseAvatar(true);
            break;
        }
    }
}


//scans this subnet for a valid server
void Game::ScanForServer()
{
    unsigned short port = 9999;
    unsigned short port_broadcast = 9999;
    clientSock.SetBlocking(false);
    bool server_found = false;
    std::string ip_string = ip.ToString();

    sf::Packet rbroadcastPacket;

    sf::IPAddress broadCastAddress("255.255.255.255");

    clientSock.Bind(port);

    cout << "Looking for server broadcast messages on port " << port_broadcast << endl;

    //Search for a UDP broadcast from the server
    if (clientSock.Receive(rbroadcastPacket, broadCastAddress , port_broadcast) == sf::Socket::Done)
    {
        rbroadcastPacket >> serverIP;
        cout << "Server found at address" << serverIP << endl;
        server_found = true;
    }


    if (!server_found)
        std::cerr <<"Server not found" << endl;

    else
    {
        sf::Packet connectPacket;
        connectPacket << "connect";
        connectPacket << ip_string;
        if (clientSock.Send(connectPacket, serverIP , port) == sf::Socket::Done)
            cout << "Connected to server! Waiting for others to join..." << endl;


        clientSock.SetBlocking(true);   //Force the client to wait for the server
        sf::Packet statusPacket;
        sf::IPAddress address(serverIP);
        string status = "Idle";

        do
        {

            if (clientSock.Receive(statusPacket, address , port) == sf::Socket::Done)
            {
                statusPacket >> status;
                if (status == "start")
                {
                    statusPacket >> numPlayers; //store number of players
                    randomizeGameState(_gameState);
                }
            }
        }
        while (status == serverIP);
        clientSock.SetBlocking(false);
    }
}

int main()
{
    Game::Start();

    return 0;
}
