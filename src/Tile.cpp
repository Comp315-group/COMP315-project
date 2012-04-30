#include "Tile.h"

//sets the image of this tile. Also updates the sprite
void Tile::setImage(sf::Image newImage)
{
    delete &sprite;
    image = newImage;
    loadSprite();
}

//constructs this tile's sprite from it's image
void Tile::loadSprite()
{
    //create sprite
    sprite.SetImage(image);

    //sprites coordinate's are the same as the tile's
    sprite.SetX(getX());
    sprite.SetY(getY());
}

//set whether or not the contents of this tile are empty
void Tile::setEmpty(bool b)
{
    empty = b;
}
