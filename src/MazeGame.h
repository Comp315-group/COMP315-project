#ifndef MAZEGAME_H_INCLUDED
#define MAZEGAME_H_INCLUDED

#include "GFX.h"
#include <SFML/Window.hpp>
#include "Map.h"
#include <iostream>

#endif // MAZEGAME_H_INCLUDED

class MazeGame
{
    bool mazeGameOver;
    Map *map;

    public:
     MazeGame();
     void draw(sf::RenderWindow &gameWindow);
     void handle_input(Player *player, sf::Event input);

     bool gameOver();
};

MazeGame::MazeGame()
{
    mazeGameOver = false;
    map = new Map("resource/map/maze.map", Map::Maze_map);
}

void MazeGame::draw(sf::RenderWindow &gameWindow)
{
    Tile *currentTile;
    //Draw maze
    for (unsigned int y = 0; y < map->getHeight(); y++)
    {
        for (unsigned int x = 0; x < map->getWidth(); x++)
        {
            currentTile = map->getTile(x, y);
            gameWindow.Draw(currentTile->getSprite());
        }
    }

    //delete currentTile;

    //Draw player
    //gameWindow.Draw(player1->getSprite());
}

bool MazeGame::gameOver()
{
    return mazeGameOver;
}

//collision detection
void MazeGame::handle_input(Player *player, sf::Event input){
    if (input.Type == sf::Event::KeyPressed){

        sf::Event currentEvent = input;
        int curX = player->getXPos();
        int curY = player->getYPos();
        const Tile *targetTile;

        if(currentEvent.Key.Code == sf::Key::Up){
            targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH, curY/WALKABLE_TILE_DEFAULT_HEIGHT-1);
            if (targetTile->getWalkability() == WALKABILITY_OK)
                player->alterY(-32);

            else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    player->move(9*32, 11*32);
                    mazeGameOver = true;
                }

        }
        if(currentEvent.Key.Code == sf::Key::Down){
             targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH, curY/WALKABLE_TILE_DEFAULT_HEIGHT+1);
            if (targetTile->getWalkability() == WALKABILITY_OK)
                player->alterY(32);

                else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    player->move(9*32, 11*32);
                    mazeGameOver = true;
                }
        }
        if(currentEvent.Key.Code == sf::Key::Left){
             targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH-1, curY/WALKABLE_TILE_DEFAULT_HEIGHT);
            if (targetTile->getWalkability() == WALKABILITY_OK)
                player->alterX(-32);

                else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    player->move(9*32, 11*32);
                    mazeGameOver = true;
                }
        }
        if(currentEvent.Key.Code == sf::Key::Right){
            targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH+1, curY/WALKABLE_TILE_DEFAULT_HEIGHT);
            if (targetTile->getWalkability() == WALKABILITY_OK)
                player->alterX(32);

                else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    player->move(9*32, 11*32);
                    mazeGameOver = true;
                }
        }
    }
}
