#ifndef MAP_H
#define MAP_H

#endif // MAP_H

#include "Tile.h"
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

    Map();
    Map(const char *fileName, std::string map_name);

    unsigned int getWidth() const{return width;}
    unsigned int getHeight() const{return height;}
    std::string getName() const {return name;}
    Tile* getTile(int xPos, int yPos){return tileset[xPos][yPos];}

    private:
        unsigned int width;
        unsigned int height;
        std::string name;
};

