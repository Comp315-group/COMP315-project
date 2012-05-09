#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

////////////////////////
////////INCLUDES////////
////////////////////////
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
#include "Player.h"
#include "MazeGame.h"
#include "OddOneGame.h"
#include "HideGame.h"
#include "MatchingGame.h"
#include "PatternGame.h"
#include "WordfillGame.h"
#include "SoundManager.h"
#include "WordSearchGame.h"
#include "MemoryGame.h"
#include "PlayerMenu.h"
#include "PickupGame.h"
#include "GameTimer.h"

////////////////////////
////PLAYER OBJECTS//////
////////////////////////
Player *player1;

int numPlayers = 0;

sf::SocketUDP clientSock;
sf::IPAddress ip;
std::string serverIP;

//flag for single player
bool solo = true;

/////////////////////////
//GAME INSTANCE CLASSES//
/////////////////////////

OddOneGame *oddonegame;
MazeGame *mazegame;
HideGame *hidegame;
MatchingGame *matchinggame;
PatternGame *patterngame;
WordfillGame *wordfilgame;
WordSearchGame *wordsearchgame;
MemoryGame *memorygame;
PickupGame *pickupgame;

//Used to display player score
sf::String score_text;

//background image and game over image as well as their associated sprites
sf::Image bgImage;
sf::Sprite bgSprite;
sf::Image gameOverImage;
sf::Sprite gameOverSprite;

//The sprite for the custom mouse cursor
sf::Sprite cursor;

//sound manager for the game
SoundManager sound_manager;

GameTimer _timekeeper(300);

//game is starting up
bool first_run = true;

class Game
{
public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowPlayMenu();
	static void ShowPlayerCreationScreen();

	static void ScanForServer();


    enum GameState { Uninitialized, ShowingSplash, Paused,
					ShowingMenu, ShowingPlayMenu, Creating_Player, Playing_odd, Playing_pattern, Playing_hide,Playing_matching, Playing_maze, Playing_wordfill, Playing_memory,
					Playing_wordsearch, Playing_pickup, Game_over, Exiting };

    static void randomizeGameState(GameState currentState);


	static GameState _gameState;
    static GameState tempGameState;
	static sf::RenderWindow _mainWindow;
};


#endif // GAME_H_INCLUDED
