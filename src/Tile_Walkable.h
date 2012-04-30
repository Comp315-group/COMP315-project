#ifndef TILE_WALKABLE_H_INCLUDED
#define TILE_WALKABLE_H_INCLUDED

#include "Tile.h"

/*
Walkability constraints, the properties of which help with collision detection.
*/
//tile can be occupied by a player
const int WALKABILITY_OK = 0;
//tile cannot be occupied by a player
const int WALKABILITY_NOT_OK = 1;
//tile is the exit tile
const int WALKABILITY_EXITABLE = 2;

//default dimensions for a walkable tile object
const int WALKABLE_TILE_DEFAULT_WIDTH = 32;
const int WALKABLE_TILE_DEFAULT_HEIGHT = 32;

class WalkableTile : public Tile
{
    private:
        //The walkability of this tile
        int walkability;

    public:
        //default constructor. Automatically invokes the Tile() constructor
        WalkableTile(sf::Image value, int xVal, int yVal, int _walkability)
            :Tile(value, xVal, yVal, WALKABLE_TILE_DEFAULT_WIDTH, WALKABLE_TILE_DEFAULT_HEIGHT)
        {
        walkability = _walkability;
        }

        //returns the walkability of this tile
        int getWalkability() const {return walkability;}

        //set the walkability of this tile
        void setWalkability(int newWalkability);
};


#endif // TILE_WALKABLE_H_INCLUDED
