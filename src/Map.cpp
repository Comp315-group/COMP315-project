#include "Map.h"

//default constructor
Map::Map()
{
    //dimensions initialised to maximum
    width = height = MAXIMUM_MAP_HEIGHT;

    //every tile in this map has the "empty" image
    sf::Image pic = load_image("resource/img/empty.bmp");

    //initialise every tile with default parameters
    for (unsigned int y = 0; y < height ; y++)
        for (unsigned int x = 0; x < width ; x++)
            tileset[x][y] = new Tile(pic, x, y, TILE_DEFAULT_WIDTH, TILE_DEFAULT_HEIGHT);
}

//parameterised constructor
Map::Map(const char *fileName, mapType type)
{
    //initialise width and height to 0
    width = height = 0;

    //create an input file stream to read from filename
    ifstream inStream(fileName);

    //error handling for the stream
    if (inStream.fail())
    {

    }

    //read in width and height from the map file, convert from string to integers
    std::string width_s;
    getline(inStream, width_s);
    width = atoi(width_s.c_str());
    std::string height_s;
    getline(inStream, height_s);
    height = atoi(height_s.c_str());

    //a character representation of this map
    char mapRepresentation[width][height];

    //build the map representation
    for (unsigned int y = 0; y < height ; y++)
    {

        //get next line from map file
        std::string line = "";
        getline(inStream, line);

        for (int x = 0; x < line.length(); x++)
        {
            mapRepresentation[x][y] = line[x];
        }

    } //Done loading tiles

    switch(type)
    {
    case Maze_map:
    {
        //we are creating a maze map

        //load images needed for maze objects
        sf::Image floorTileImg = load_image("resource/img/maze/floor.bmp");
        sf::Image emptyImg = load_image("resource/img/maze/empty.bmp");
        sf::Image wallTileImg = load_image("resource/img/maze/wall_stone.png");
        sf::Image doorImg = load_image("resource/img/maze/wooden_door_open.png");

        //build tileset from the map representation. This is a one-to-one mapping
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                switch (mapRepresentation[x][y])
                {
                    //empty tile
                case '0':
                    tileset[x][y] = new WalkableTile(emptyImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_NOT_OK);
                    tileset[x][y]->setEmpty(true);
                    break;

                    //wall tile
                case '#':
                    tileset[x][y] = new WalkableTile(wallTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_NOT_OK);
                    break;

                    //floor tile
                case '.':
                    tileset[x][y] = new WalkableTile(floorTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_OK);
                    break;

                    //exit tile
                case 'e':
                    tileset[x][y] = new WalkableTile(doorImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_EXITABLE);
                    break;

                    //start tile
                case 's':
                    tileset[x][y] = new WalkableTile(floorTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_OK);
                    startTile = tileset[x][y];
                    break;

                }
            }
        break;
    }

    case Pickup_map:
    {
        //we are creating a pickup map

        //load images needed for pickup objects
        sf::Image floorTileImg = load_image("resource/img/pickup/floor.bmp");
        sf::Image emptyImg = load_image("resource/img/pickup/empty.bmp");
        sf::Image wallTileImg = load_image("resource/img/pickup/wall_stone.png");

        //build tileset from the map representation. This is a one-to-one mapping
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                switch (mapRepresentation[x][y])
                {
                    //empty tile
                case '0':
                    tileset[x][y] = new WalkableTile(emptyImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_NOT_OK);
                    tileset[x][y]->setEmpty(true);
                    break;

                    //wall tile
                case '#':
                    tileset[x][y] = new WalkableTile(wallTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_NOT_OK);
                    break;

                    //floor tile
                case '.':
                    tileset[x][y] = new WalkableTile(floorTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_OK);
                    break;

                    //numbertile
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                {

                    sf::Image tileIMG = load_image("resource/img/pickup/" + toString(mapRepresentation[x][y]) + ".bmp");
                    tileset[x][y] = new NumberTile(tileIMG, floorTileImg, x*NUMBER_TILE_DEFAULT_WIDTH, y*NUMBER_TILE_DEFAULT_HEIGHT, mapRepresentation[x][y] - '0');
                    break;
                }

                //start tile
                case 's':
                {
                    tileset[x][y] = new WalkableTile(floorTileImg, x*WALKABLE_TILE_DEFAULT_WIDTH, y*WALKABLE_TILE_DEFAULT_HEIGHT, WALKABILITY_OK);
                    startTile = tileset[x][y];
                    break;

                }
                }
            }
        break;
    }
    //close file input stream
    inStream.close();
    }
}

/*
    return the start tile associated with this map
*/
Tile* Map::getStartTile()
{
    return startTile;
}

/*
    destructor deletes the tileset
*/
Map::~Map()
{
    delete [] tileset;
}
