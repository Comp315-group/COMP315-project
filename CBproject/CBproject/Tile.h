#ifndef TILE_H
#define TILE_H

#endif // TILE_H

#include <SFML/Graphics.HPP>
#include "GFX.h"
#include <string>

/*
Walkability constraints, the properties of which help with collision detection.
*/
const int WALKABILITY_OK = 0;   //tile can be occupied by a player
const int WALKABILITY_NOT_OK = 1;   //tile cannot be occupied by a player

const int TILE_WIDTH = 32;  //width of all tiles if they're uniform
const int TILE_HEIGHT = 32; //height of all tiles if they're uniform

class Tile{

public:
    Tile()
        :walkability(WALKABILITY_NOT_OK), x(0), y(0), name("unnamed")
        {}
    Tile(sf::Image value, int walk, int xVal, int yVal, std::string _name)
        :image(value), walkability(walk), x(xVal), y(yVal), name(_name)
        {}

    sf::Image getImage() const{return image;}   //returns the image object associated with this tile
    sf::Sprite getSprite() const{return sprite;}    //returns the sprite object associated with this tile
    int getWalkability() const {return walkability;}    //returns the walkability of this tile
    unsigned int getX() const {return x;}   //returns the X coordinate of this tile
    unsigned int getY() const {return y;}   //returns the Y coordinate of this tile
    std::string getName() const {return name;}  //returns the name associated with this tile
    int getTileWidth() const{return TILE_WIDTH;}    //returns the width of this tile
    int getTileHeight() const{return TILE_HEIGHT;}  //returns the height of this tile
    void setImage(sf::Image newImage);     //sets the image of this tile
    void loadSprite();  //constructs this tile's sprite from it's image
    void setWalkability(int newWalkability);    //set the walkability of this tile

private:
    sf::Image image;    //The image object associated with this tile
    sf::Sprite sprite;  //The sprite object associated with this tile
    int walkability;    //The walkability of this tile
    unsigned int x; //The X coordinate of this tile
    unsigned int y; //The Y coordinate of this tile
    std::string name;   //The name of this tile
};


