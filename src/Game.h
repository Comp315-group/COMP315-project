#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"


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
					ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};


#endif // GAME_H_INCLUDED
