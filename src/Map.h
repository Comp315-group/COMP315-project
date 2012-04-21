#ifndef MAP_H
#define MAP_H

#endif // MAP_H

#include "Tile_Walkable.h"
#include <fstream>
#include <string>
#include "LibTools.h"
#include "GFX.h"

#include <SFML/Graphics.hpp>

const int MAXIMUM_MAP_WIDTH = 64;
const int MAXIMUM_MAP_HEIGHT = 64;

class Map{

    public:
    Tile* tileset[MAXIMUM_MAP_HEIGHT][MAXIMUM_MAP_WIDTH];
    enum mapType {Maze_map, WordSearch_map, Memory_map};

    Map();
    Map(const char *fileName, mapType type);

    unsigned int getWidth() const{return width;}
    unsigned int getHeight() const{return height;}
    Tile* getTile(int xPos, int yPos){return tileset[xPos][yPos];}

    private:
        unsigned int width;
        unsigned int height;
};

