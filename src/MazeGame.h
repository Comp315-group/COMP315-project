#ifndef MAZEGAME_H_INCLUDED
#define MAZEGAME_H_INCLUDED

////////////////////////
////////INCLUDES////////
////////////////////////

#include "GFX.h"
#include <SFML/Window.hpp>
#include "Map.h"

#endif // MAZEGAME_H_INCLUDED

class MazeGame
{
    //records whether or not the maze has been solved
    bool mazeGameOver;

    //floating text telling the player to exit the maze
    sf::String mazeText;

    public:
    //default constructor
     MazeGame();

     //draw maze-components to a specified window
     void draw(sf::RenderWindow &gameWindow);

     //process input for a specified player
     void handle_input(Player *player, sf::Event input);

     //set the start tile of the player
     void setPlayerStartLocation(Player *player);

     //returns whether or nor the player has solved the maze
     bool gameOver();

    //the map object associated with this maze
    Map *map;

};

MazeGame::MazeGame()
{
    //game not over
    mazeGameOver = false;

    //seed RNG
    srand(time(0));

    //choose random maze
    int num = rand() % 4;
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

        case 3:
            map = new Map("resource/map/maze4.map", Map::Maze_map);
            break;

        default:
            map = new Map("resource/map/maze1.map", Map::Maze_map);
            break;
    }

    //initialise maze text
    mazeText.SetText("Escape the maze!");
    mazeText.SetSize(80);
    mazeText.SetColor(sf::Color ::Blue);
    mazeText.SetPosition(175,25);
}

/*
    Set the player start location to the same coordinates as the start tile of the map object
*/
void MazeGame::setPlayerStartLocation(Player *player)
{
    int x = map->getStartTile()->getX();
    int y = map->getStartTile()->getY();

    player->move(x, y);
}

/*
    Draw tiles to screen as well as the maze text
*/
void MazeGame::draw(sf::RenderWindow &gameWindow)
{
    Tile *currentTile;

    //Draw non-empty tiles to screen
    for (unsigned int y = 0; y < map->getHeight(); y++)
    {
        for (unsigned int x = 0; x < map->getWidth(); x++)
        {
            currentTile = map->getTile(x, y);
            if (!currentTile->isEmpty())
                gameWindow.Draw(currentTile->getSprite());
        }
    }

    //draw Text
    gameWindow.Draw(mazeText);
}

/*
    Returns whether or not the player has solved the maze
*/
bool MazeGame::gameOver()
{
    return mazeGameOver;
}

//collision detection
void MazeGame::handle_input(Player *player, sf::Event input){
    if (input.Type == sf::Event::KeyPressed){

        sf::Event currentEvent = input;

        //get player coordinates
        int curX = player->getXPos();
        int curY = player->getYPos();

        //a pointer to the tile that the player wishes to move to
        const Tile *targetTile;

        //up was pressed
        if(currentEvent.Key.Code == sf::Key::Up){
            //target tile is 1 tile up from the player's location
            targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH, curY/WALKABLE_TILE_DEFAULT_HEIGHT-1);

            //target tile can be walked on
            if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterY(-32);

            //target tile is the exit tile
            else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
            {
                   //game is over
                    mazeGameOver = true;
            }

        }

        //down was pressed
        if(currentEvent.Key.Code == sf::Key::Down){
            //target tile is 1 tile down from the player's location
             targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH, curY/WALKABLE_TILE_DEFAULT_HEIGHT+1);

            //target tile can be walked on
            if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterY(32);

                //target tile is the exit tile
                else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    //game is over
                    mazeGameOver = true;
                }
        }

        //left was pressed
        if(currentEvent.Key.Code == sf::Key::Left){
            //target tile is 1 tile left of the player's location
             targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH-1, curY/WALKABLE_TILE_DEFAULT_HEIGHT);

             //target tile can be walked on
            if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterX(-32);

                //target tile is the exit tile
                else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    //game is over
                    mazeGameOver = true;
                }
        }

        //right was pressed
        if(currentEvent.Key.Code == sf::Key::Right){
            //target tile is 1 tile right of the player's location
            targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH+1, curY/WALKABLE_TILE_DEFAULT_HEIGHT);

            //target tile can be walked on
            if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterX(32);

                //target tile is the exit tile
                else if (targetTile->getWalkability() == WALKABILITY_EXITABLE)
                {
                    //game over
                    mazeGameOver = true;
                }
        }
    }
}
