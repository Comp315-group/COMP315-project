////////////////////////
////////INCLUDES////////
////////////////////////

#include "GFX.h"
#include <SFML/Window.hpp>
#include "Map.h"

class PickupGame
{
    //records whether or not the player has picked up all the numbers
    bool pickupGameOver;

    //floating text telling the player what to do
    sf::String pickupText;

    int curNum;

    bool pickup(int num);

    public:
    //default constructor
     PickupGame();

     //draw pickup-components to a specified window
     void draw(sf::RenderWindow &gameWindow);

     //process input for a specified player
     void handle_input(Player *player, sf::Event input);

     //set the start tile of the player
     void setPlayerStartLocation(Player *player);

     //returns whether or nor the player has picked up all the numbers
     bool pickUpGameOver();

    //the map object associated with this pickup game
    Map *map;

};

PickupGame::PickupGame()
{

    //Which number needs to be picked up next
    curNum = 1;

    //game not over
    pickupGameOver = false;

    //seed RNG
    srand(time(0));

    //choose random maze
    int num = rand() % 4;


    switch (num)
    {
        case 0:
            map = new Map("resource/map/pickup/pickup1.map", Map::Pickup_map);
            break;

        case 1:
            map = new Map("resource/map/pickup/pickup2.map", Map::Pickup_map);
            break;

        case 2:
            map = new Map("resource/map/pickup/pickup3.map", Map::Pickup_map);
            break;

        case 3:
            map = new Map("resource/map/pickup/pickup4.map", Map::Pickup_map);
            break;

        default:
            map = new Map("resource/map/pickup/pickup1.map", Map::Pickup_map);
            break;
    }

    //initialise pickup text
    pickupText.SetText("Using the arrows pick up all the \n numbers in the correct order!");
    pickupText.SetSize(60);
    pickupText.SetColor(sf::Color ::Red);
    pickupText.SetPosition(125,25);
}

//handles logic for a pickup attempt
bool PickupGame::pickup(int _num)
{
    int tileNum = _num;
    if (tileNum == curNum)
    {
        curNum++;
        if (curNum == 6)
            pickupGameOver = true;
        return true;
    }
    return false;
}

/*
    Set the player start location to the same coordinates as the start tile of the map object
*/
void PickupGame::setPlayerStartLocation(Player *player)
{
    int x = map->getStartTile()->getX();
    int y = map->getStartTile()->getY();

    player->move(x, y);
}

/*
    Draw tiles to screen as well as the maze text
*/
void PickupGame::draw(sf::RenderWindow &gameWindow)
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
    gameWindow.Draw(pickupText);
}

/*
    Returns whether or not the player has solved the maze
*/
bool PickupGame::pickUpGameOver()
{
    return pickupGameOver;
}

//collision detection
void PickupGame::handle_input(Player *player, sf::Event input){
    if (input.Type == sf::Event::KeyPressed){

        sf::Event currentEvent = input;

        //get player coordinates
        int curX = player->getXPos();
        int curY = player->getYPos();

        //a pointer to the tile that the player wishes to move to
        Tile *targetTile;

        //up was pressed
        if(currentEvent.Key.Code == sf::Key::Up){
            //target tile is 1 tile up from the player's location
            targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH, curY/WALKABLE_TILE_DEFAULT_HEIGHT-1);

            int num = targetTile->getNumber();

            if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterY(-32);

            if (num != 0)
            {
                if (pickup(num))
                {
                    targetTile->_removeNumberImage();
                }
            }

        }

        //down was pressed
        if(currentEvent.Key.Code == sf::Key::Down){
            //target tile is 1 tile down from the player's location
             targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH, curY/WALKABLE_TILE_DEFAULT_HEIGHT+1);

             int num = targetTile->getNumber();

             if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterY(32);

            if (num != 0)
            {
                if (pickup(num))
                {
                    targetTile->_removeNumberImage();
                }
            }

        }

        //left was pressed
        if(currentEvent.Key.Code == sf::Key::Left){
            //target tile is 1 tile left of the player's location
             targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH-1, curY/WALKABLE_TILE_DEFAULT_HEIGHT);

             int num = targetTile->getNumber();

             if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterX(-32);

            if (num != 0)
            {
                if (pickup(num))
                {
                    targetTile->_removeNumberImage();
                }
            }

        }

        //right was pressed
        if(currentEvent.Key.Code == sf::Key::Right){
            //target tile is 1 tile right of the player's location
            targetTile = map->getTile(curX/WALKABLE_TILE_DEFAULT_WIDTH+1, curY/WALKABLE_TILE_DEFAULT_HEIGHT);

            int num = targetTile->getNumber();

            if (targetTile->getWalkability() == WALKABILITY_OK)
                //move player
                player->alterX(32);

            if (num != 0)
            {
                if (pickup(num))
                {
                    targetTile->_removeNumberImage();
                }
            }

        }
    }
}
