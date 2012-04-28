#ifndef TILE_H
#define TILE_H

#endif // TILE_H

#include <SFML/Graphics.HPP>
#include "GFX.h"
#include <string>



const int TILE_DEFAULT_WIDTH = 32;  //width of all tiles if they're uniform
const int TILE_DEFAULT_HEIGHT = 32; //height of all tiles if they're uniform

class Tile{

public:
    Tile()
       :x(0), y(0), width(TILE_DEFAULT_WIDTH), height(TILE_DEFAULT_HEIGHT)
        {}
    Tile(sf::Image value, int xVal, int yVal, int width_, int height_)
        :image(value), x(xVal), y(yVal), width(width_), height(height_)
        {loadSprite();}

    sf::Image getImage() const{return image;}   //returns the image object associated with this tile
    sf::Sprite getSprite() const{return sprite;}    //returns the sprite object associated with this tile
    unsigned int getX() const {return x;}   //returns the X coordinate of this tile
    unsigned int getY() const {return y;}   //returns the Y coordinate of this tile
    int getTileWidth() const{return width;}    //returns the width of this tile
    int getTileHeight() const{return height;}  //returns the height of this tile
    void setImage(sf::Image newImage);     //sets the image of this tile
    void loadSprite();  //constructs this tile's sprite from it's image

    virtual int getWalkability() const{ return 0; }

protected:
    sf::Image image;    //The image object associated with this tile
    sf::Sprite sprite;  //The sprite object associated with this tile
    unsigned int x; //The X coordinate of this tile
    unsigned int y; //The Y coordinate of this tile
    unsigned int width;
    unsigned int height;
};


