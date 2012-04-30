#ifndef MAP_H
#define MAP_H

#endif // MAP_H

#include "Tile_Walkable.h"
#include <fstream>
#include <string>
#include "LibTools.h"
#include "GFX.h"

#include <SFML/Graphics.hpp>

/*
    The map is bound to a 64x64 grid of tiles, however a tileset does not have to be this big
*/
const int MAXIMUM_MAP_WIDTH = 64;
const int MAXIMUM_MAP_HEIGHT = 64;

class Map{

    public:
        //The 2D-array of tiles associated with this map class
        Tile* tileset[MAXIMUM_MAP_HEIGHT][MAXIMUM_MAP_WIDTH];

        //The type of maps available
        enum mapType {Maze_map, WordSearch_map, Memory_map};

    //Default constructor
    Map();
    //Parameterised constructor
    Map(const char *fileName, mapType type);

    //returns the width of this map i.e the length of the tileset in the horizontal plane
    unsigned int getWidth() const{return width;}
   //returns the height of this map i.e the length of the tileset in the vertical plane
    unsigned int getHeight() const{return height;}

    //returns a pointer to the Tile at position (xPos, yPos)
    Tile* getTile(int xPos, int yPos){return tileset[xPos][yPos];}

    //returns the starting tile associated with this map
    Tile* getStartTile();

    //destructor
    ~Map();

    private:
        //The width of the non-null tileset
        unsigned int width;
        //The height of the non-null tileset
        unsigned int height;

        //The tile that the player starts on for this map
        Tile *startTile;
};

