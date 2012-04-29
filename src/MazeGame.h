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
    sf::String mazeText;

    public:
     MazeGame();
     void draw(sf::RenderWindow &gameWindow);
     void handle_input(Player *player, sf::Event input);
     void setPlayerStartLocation(Player *player);
     bool gameOver();

    Map *map;

};

MazeGame::MazeGame()
{
    mazeGameOver = false;
    srand(time(0));
    int num = rand() % 3;   //choose random maze

    switch (num)
    {
        case 0:
            map = new Map("resource/map/maze1.map", Map::Maze_map);
            break;

        case 1:
            map = new Map("resource/map/maze2.map", Map::Maze_map);
            break;

        case 2:
            map = new Map("resource/map/maze3.map", Map::Maze_map);
            break;

        default:
            map = new Map("resource/map/maze1.map", Map::Maze_map);
            break;
    }

    mazeText.SetText("Escape the maze!");
    mazeText.SetSize(80);
    mazeText.SetColor(sf::Color ::Blue);
    mazeText.SetPosition(175,25);
}

void MazeGame::setPlayerStartLocation(Player *player)
{
    int x = map->getStartTile()->getX();
    int y = map->getStartTile()->getY();

    player->move(x, y);
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

    //draw Text
    gameWindow.Draw(mazeText);

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
