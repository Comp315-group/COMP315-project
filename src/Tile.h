#ifndef TILE_H
#define TILE_H

#endif // TILE_H

#include <SFML/Graphics.HPP>
#include "GFX.h"
#include <string>


//default dimensions for tile objects
const int TILE_DEFAULT_WIDTH = 32;
const int TILE_DEFAULT_HEIGHT = 32;

class Tile{

public:
    //default constructor
    Tile()
       :x(0), y(0), width(TILE_DEFAULT_WIDTH), height(TILE_DEFAULT_HEIGHT)
        {}
    //parameterised constructor
    Tile(sf::Image value, int xVal, int yVal, int width_, int height_)
        :image(value), x(xVal), y(yVal), width(width_), height(height_)
        {
            //tile is set to non-empty by default
            empty = false;
            //load the sprite for this tile from the image
            loadSprite();
        }

    //returns the image object associated with this tile
    sf::Image getImage() const{return image;}
    //returns the sprite object associated with this tile
    sf::Sprite getSprite() const{return sprite;}

    //returns the X coordinate of this tile
    unsigned int getX() const {return x;}
    //returns the Y coordinate of this tile
    unsigned int getY() const {return y;}

    //returns the width of this tile
    int getTileWidth() const{return width;}
    //returns the height of this tile
    int getTileHeight() const{return height;}

    //sets the image of this tile
    void setImage(sf::Image newImage);
    //constructs this tile's sprite from it's image
    void loadSprite();

    //returns whether or not this tile is an empty tile
    bool isEmpty() const {return empty;};
    //set the empty status of this tile
    void setEmpty(bool b);

    //virtual function needed for Walkable tile objects here. This is to accomodate downcasting
    virtual int getWalkability() const{ return 0; }

protected:
    //the image object associated with this tile
    sf::Image image;
    //the sprite object associated with this tile
    sf::Sprite sprite;

    //the X coordinate of this tile
    unsigned int x;
    //the Y coordinate of this tile
    unsigned int y;

    //the width of this tile
    unsigned int width;
    //the height of this tile
    unsigned int height;

    //keeps track of whether or not this tile is empty
    bool empty;
};


