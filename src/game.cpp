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
#include "SplashScreen.h"

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
	_mainWindow.Create(sf::VideoMode(1024,768,32),"EduGame");

    //create player object(s)
    player1 = new Player("lunch", load_image("resource/img/player.bmp"));

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
	mazegame = new MazeGame();
	mazegame->setPlayerStartLocation(player1);
	hidegame = new HideGame();
	matchinggame = new MatchingGame();
	wordfilgame = new WordfillGame();

	//seed RNG
	srand(time(0));

    //initialise the sound manager
	sound_manager.init();

    //initialise the text that notifies the player about their score
    score_text.SetText("Score : " + toString(player1->getScore()));
    score_text.SetSize(30);
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

                        //update the main window
                        _mainWindow.Display();

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

                    //update main window
                    _mainWindow.Display();

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
                    if(currentEvent.Type == currentEvent.MouseButtonPressed  && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          //get click coordinates
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;

                        if((posx >= 10 && posx <= 1000) && (posy >= 250 && posy <= 500)){
                            oddonegame->correct(posx, posy);
                            oddonegame->drawText(_mainWindow);

                            if(oddonegame->gameOver())
                            {
                                sound_manager.playCorrectSound();
                                score_text.SetColor(sf::Color::Green);
                                player1->incrementScore(10);
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

			case Game::Playing_hide:
			{

            sf::Event currentEvent;

            if (hidegame == NULL)
                hidegame = new HideGame();

            while(_mainWindow.GetEvent(currentEvent))
					{
					_mainWindow.Clear(sf::Color(0,0,0));
                    _mainWindow.Draw(bgSprite);
                    hidegame->draw(_mainWindow);

                    //Update and draw player score to screen
                    score_text.SetText("Score : " + toString(player1->getScore()));
                    _mainWindow.Draw(score_text);


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

                    if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;


                       if((posx >= 125 && posx <= 875) && (posy >= 200 && posy <= 650)){
                           hidegame->correct(posx, posy);
                           hidegame->DrawText(_mainWindow);

                           if (hidegame->gameOver())
                           {
                               sound_manager.playCorrectSound();
                               score_text.SetColor(sf::Color::Green);
                               player1->incrementScore(20);
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

                    if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;


                       if((posx >= 40 && posx <= 980) && (posy >= 375 && posy <= 590)){
                            matchinggame->correct(posx, posy);
                            matchinggame->drawText(_mainWindow);

                            if (matchinggame->gameOver())
                            {
                               sound_manager.playCorrectSound();
                               score_text.SetColor(sf::Color::Green);
                               player1->incrementScore(20);
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

                    if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;

                       if((posx >= 190 && posx <= 810) && (posy >= 400 && posy <= 600)){
                            patterngame->correct(posx, posy);
                            patterngame->drawText(_mainWindow);

                           if (patterngame->gameOver())
                           {
                               sound_manager.playCorrectSound();
                               score_text.SetColor(sf::Color::Green);
                               player1->incrementScore(20);
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

        case Game::Playing_wordfill:{
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

                    _mainWindow.Display();

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

                    if(currentEvent.Type == currentEvent.MouseButtonPressed  && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                          int posx = currentEvent.MouseButton.X;
                          int posy = currentEvent.MouseButton.Y;

                        if((posx >= 320 && posx <= 720) && (posy >= 400 && posy <= 600)){

                            wordfilgame->correct(posx, posy);

                            if(wordfilgame->gameOver())
                            {
                                sound_manager.playCorrectSound();
                                score_text.SetColor(sf::Color::Green);
                                player1->incrementScore(20);
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

                if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                    int posx = currentEvent.MouseButton.X;
                    int posy = currentEvent.MouseButton.Y;

                    if((posx >= 400 && posx <= 625) && (posy >= 300 && posy <= 525)){
                        wordsearchgame->update(posx, posy);
                        wordsearchgame->drawText(_mainWindow);

                        if (wordsearchgame->gameOver())
                        {
                            sound_manager.playCorrectSound();
                            score_text.SetColor(sf::Color::Green);
                            player1->incrementScore(10);
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

                if(currentEvent.Type == currentEvent.MouseButtonPressed && currentEvent.MouseButton.Button == sf:: Mouse::Left){
                    int posx = currentEvent.MouseButton.X;
                    int posy = currentEvent.MouseButton.Y;

                    if((posx >= 375 && posx <= 675) && (posy >= 275 && posy <= 575)){
                        memorygame->update(posx, posy, _mainWindow);

                        if (memorygame->gameOver())
                        {
                            sound_manager.playCorrectSound();
                            score_text.SetColor(sf::Color::Green);
                            player1->incrementScore(50);
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


            //a player has won the game
            case Game::Game_over:
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
                    _mainWindow.Display();

                    //close button clicked
                    if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

                    //key pressed
                    if(currentEvent.Type == sf::Event::KeyPressed)
                    {
                            //game returns to the menu
						    _gameState = ShowingMenu;
                    }
                }
                break;
            }
    }

    //Win condition has been met
	if (player1->getScore() >= 200)
	{
            //stop main music
            sound_manager.stopBGMusic();
            //play appropriate game over sound
            sound_manager.playGameOverSound();

            //set game state to indicate that the game is over
            _gameState = Game_over;
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

    //start playing background music
    sound_manager.playBGMusic();

	//get result
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
        //exit was clicked
        case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
        //play was clicked
		case MainMenu::Play:
		//if the player paused the game before, this resumes the game
		if (_gameState == Paused)
            _gameState = tempGameState;

        //start game by randomizing the game state
        else
            //hack for now to fix a bug
             score_text.SetX(0);
             score_text.SetY(0);
			_gameState = Creating_Player;
			break;
	}
}

/*
    Randomly determines what the next game to be played is. Ensures that the same game is never played
    twice in a row
*/
void Game::randomizeGameState(Game::GameState currentState)
{
    int random = rand() % 8;

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
    }

    //ensures that the same game can never be played twice in a row
    while (random == cur)
        random = rand() % 8;

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
                randomizeGameState(_gameState);

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

int main()
{
    Game::Start();

    return 0;
}
