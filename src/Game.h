#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

////////////////////////
////////INCLUDES////////
////////////////////////
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Player.h"
#include "MazeGame.h"
#include "OddOneGame.h"
#include "HideGame.h"
#include "MatchingGame.h"
#include "PatternGame.h"
#include "GameTimer.h"
#include "SoundManager.h"

////////////////////////
////PLAYER OBJECTS//////
////////////////////////
Player *player1;

/////////////////////////
//GAME INSTANCE CLASSES//
/////////////////////////

OddOneGame *oddonegame;
MazeGame *mazegame;
HideGame *hidegame;
MatchingGame *matchinggame;
PatternGame *patterngame;

//Used to display player score
sf::String score_text;

//background image and game over image as well as their associated sprites
sf::Image bgImage;
sf::Sprite bgSprite;
sf::Image gameOverImage;
sf::Sprite gameOverSprite;

//sound manager for the game
SoundManager sound_manager;

class Game
{
public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();


    enum GameState { Uninitialized, ShowingSplash, Paused,
					ShowingMenu, Playing_odd, Playing_pattern, Playing_hide,Playing_matching, Playing_maze, Game_over, Exiting };

    static void randomizeGameState(GameState currentState);


	static GameState _gameState;
    static GameState tempGameState;
	static sf::RenderWindow _mainWindow;
};


#endif // GAME_H_INCLUDED
