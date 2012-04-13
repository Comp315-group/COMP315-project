#include "GFX.h"

//load an image from a file
sf::Image load_image(std::string filename )
{
    sf::Image tempImage;
    tempImage.LoadFromFile(filename);
    createMask(tempImage);
    tempImage.SetSmooth(false);
    return tempImage;
}

//create a mask for an image
void createMask(sf::Image &image)
{
image.CreateMaskFromColor(sf::Color(0, 255, 255), 0);
}
