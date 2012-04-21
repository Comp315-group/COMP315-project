#ifndef TILE_H
#define TILE_H

#endif // TILE_H

#include <SFML/Graphics.HPP>
#include "GFX.h"
#include <string>



const int TILE_WIDTH = 32;  //width of all tiles if they're uniform
const int TILE_HEIGHT = 32; //height of all tiles if they're uniform

class Tile{

public:
    Tile()
       :x(0), y(0)
        {}
    Tile(sf::Image value, int xVal, int yVal)
        :image(value), x(xVal), y(yVal)
        {}

    sf::Image getImage() const{return image;}   //returns the image object associated with this tile
    sf::Sprite getSprite() const{return sprite;}    //returns the sprite object associated with this tile
    unsigned int getX() const {return x;}   //returns the X coordinate of this tile
    unsigned int getY() const {return y;}   //returns the Y coordinate of this tile
    int getTileWidth() const{return TILE_WIDTH;}    //returns the width of this tile
    int getTileHeight() const{return TILE_HEIGHT;}  //returns the height of this tile
    void setImage(sf::Image newImage);     //sets the image of this tile
    void loadSprite();  //constructs this tile's sprite from it's image

protected:
    sf::Image image;    //The image object associated with this tile
    sf::Sprite sprite;  //The sprite object associated with this tile
    unsigned int x; //The X coordinate of this tile
    unsigned int y; //The Y coordinate of this tile
};


