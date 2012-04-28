#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "MazeGame.h"
#include "OddOneGame.h"
#include "HideGame.h"
#include "MatchingGame.h"
#include "PatternGame.h"

Player *player1;
OddOneGame *oddonegame;
MazeGame *mazegame;
HideGame *hidegame;
MatchingGame *matchinggame;
PatternGame *patterngame;


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
					ShowingMenu, Playing_odd, Playing_pattern, Playing_hide,Playing_matching, Playing_maze, Exiting };

    static void randomizeGameState();


	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};


#endif // GAME_H_INCLUDED
