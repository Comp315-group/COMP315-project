#include "Map.h"

Map::Map()
{
    width = height = MAXIMUM_MAP_HEIGHT;
    sf::Image pic = load_image("resource/img/tile0.bmp");

    for (unsigned int y = 0; y < height ; y++)
        for (unsigned int x = 0; x < width ; x++)
            tileset[x][y] = new Tile(pic, x, y, TILE_DEFAULT_WIDTH, TILE_DEFAULT_HEIGHT);
}

Map::Map(const char *fileName, mapType type)
{
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

    char mapRepresentation[width][height];

    for (unsigned int y = 0; y < height ; y++)
    {
        std::string line = "";
        getline(inStream, line);    //get next line from map file

        for (int x = 0; x < line.length(); x++)
        {
            mapRepresentation[x][y] = line[x];
        }

    } //Done loading tiles


    switch(type)
    {
        case Maze_map:
        sf::Image floorTileImg = load_image("resource/img/floor.bmp");
        sf::Image emptyImg = load_image("resource/img/empty.bmp");
        sf::Image wallTileImg = load_image("resource/img/wall_stone.png");
        sf::Image doorImg = load_image("resource/img/wooden_door_closed.png");
            for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                {
                    switch (mapRepresentation[x][y])
                    {
                        case '9':
                            tileset[x][y] = new WalkableTile(emptyImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_NOT_OK);
                        break;

                        case '1':
                            tileset[x][y] = new WalkableTile(wallTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_NOT_OK);
                        break;

                        case '0':
                            tileset[x][y] = new WalkableTile(floorTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_OK);
                        break;

                        case 'C':
                            tileset[x][y] = new WalkableTile(doorImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_EXITABLE);
                        break;
                    }
                    //tileset[x][y]->loadSprite(); //Create sprite from the associated image
                }
            break;
    }

    inStream.close();
}

Map::~Map()
{
    delete [] tileset;
}
