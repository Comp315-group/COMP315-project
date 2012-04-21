#ifndef MAZEGAME_H_INCLUDED
#define MAZEGAME_H_INCLUDED

#include "GFX.h"
#include <SFML/Window.hpp>
#include "Map.h"
#endif // MAZEGAME_H_INCLUDED

class MazeGame
{
    bool mazeGameOver;
    Map *map;

    public:
     MazeGame();
     void draw(sf::RenderWindow &gameWindow);
     bool gameOver();
};

MazeGame::MazeGame()
{
    mazeGameOver = false;
    map = new Map("resource/map/maze.map", Map::Maze_map);
}

void MazeGame::draw(sf::RenderWindow &gameWindow)
{
    for (unsigned int y = 0; y < map->getHeight(); y++)
    {
        for (unsigned int x = 0; x < map->getWidth(); x++)
        {
            Tile *currentTile = map->getTile(x, y);
            gameWindow.Draw(currentTile->getSprite());
        }
    }
}

bool MazeGame::gameOver()
{
    return mazeGameOver;
}
