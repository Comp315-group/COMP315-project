#ifndef NUMBER_TILE_INCLUDED
#define NUMBER_TILE_INCLUDED

#include "Tile.h"

/*
Walkability constraints, the properties of which help with collision detection.
*/

//default dimensions for a walkable tile object
const int NUMBER_TILE_DEFAULT_WIDTH = 32;
const int NUMBER_TILE_DEFAULT_HEIGHT = 32;

class NumberTile : public Tile
{
private:
    //The number of this tile
    int number;

    //The normal walkable tile image
    sf::Image altImage;

public:
    //default constructor. Automatically invokes the Tile() constructor
    NumberTile(sf::Image value, sf::Image _altImage, int xVal, int yVal, int _number)
        :Tile(value, xVal, yVal, NUMBER_TILE_DEFAULT_WIDTH, NUMBER_TILE_DEFAULT_HEIGHT)
    {
        number = _number;
        altImage = _altImage;
    }

    //returns the number of this tile
    int getNumber() const { return number; }

    //set the walkability of this tile
    void setNumber(int newNumber);

    void _removeNumberImage();
};

inline void NumberTile::_removeNumberImage()
{
    setImage(altImage);
    number = -1;
}

#endif
