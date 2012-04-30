#include "GFX.h"

/*
    Load an image from file
*/
sf::Image load_image(std::string filename )
{
    sf::Image tempImage;
    tempImage.LoadFromFile(filename);
    createMask(tempImage);
    tempImage.SetSmooth(false);
    return tempImage;
}

/*
    Create a mask for an image
    The current mask is the colour turquoise
*/
void createMask(sf::Image &image)
{
    image.CreateMaskFromColor(sf::Color(0, 255, 255), 0);
}
