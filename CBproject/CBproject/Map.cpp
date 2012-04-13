#include "Map.h"

Map::Map()
{
    width = height = MAXIMUM_MAP_HEIGHT;
    name = "noname";
    sf::Image pic = load_image("resource/img/tile0.bmp");

    for (unsigned int y = 0; y < height ; y++)
        for (unsigned int x = 0; x < width ; x++)
            tileset[x][y] = new Tile(pic, WALKABILITY_NOT_OK, x, y, "unnamed");
}

Map::Map(const char *fileName, std::string map_name)
{

    name = map_name;

    width = height = 0;
    ifstream inStream(fileName);

    if (inStream.fail())
    {

    }
    std::string width_s;
    getline(inStream, width_s);
    width = atoi(width_s.c_str());
    std::string height_s;
    getline(inStream, height_s);
    height = atoi(height_s.c_str());

    sf::Image emptyTile = load_image("resource/img/empty.bmp");
    sf::Image wallTile = load_image("resource/img/wall_stone.png");
    sf::Image floorTile = load_image("resource/img/floor.bmp");
    sf::Image trollTile = load_image("resource/img/troll face.bmp");
    sf::Image closedDoorTile = load_image("resource/img/wooden_door_closed.png");
    sf::Image openDoorTile = load_image("resource/img/wooder_door_open.png");

    for (unsigned int y = 0; y < height ; y++)
    {

            std::string line = "";
            getline(inStream, line);
/*
            for (unsigned int x = 0; x < line.length(); x++)
            {

                switch (line[x])
                {
                    case '9':
                    tileset[x][y] = new Tile(emptyTile, WALKABILITY_NOT_OK, x*TILE_WIDTH, y*TILE_HEIGHT, "EMPTY");
                    break;

                    case '1':
                    tileset[x][y] = new Tile(wallTile, WALKABILITY_NOT_OK, x*TILE_WIDTH, y*TILE_HEIGHT, "WALL");
                    break;

                    case '0':
                    tileset[x][y] = new Tile(floorTile, WALKABILITY_OK, x*TILE_WIDTH, y*TILE_HEIGHT, "FLOOR");
                    break;

                    case 'T':
                    tileset[x][y] = new Tile(trollTile, WALKABILITY_OK, x*TILE_WIDTH, y*TILE_HEIGHT, "TROLL");
                    break;

                    case 'C':
                    exitTile = new Tile(closedDoorTile, WALKABILITY_NOT_OK, x*TILE_WIDTH, y*TILE_HEIGHT, "CLOSED_DOOR");
                    tileset[x][y] = exitTile;
                    break;


                }
                tileset[x][y]->loadSprite();
            }*/
    } //Done loading tiles


    inStream.close();
}
