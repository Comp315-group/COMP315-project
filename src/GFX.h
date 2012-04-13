#ifndef GFX_H
#define GFX_H

#include <string>
#include <SFML/Graphics.hpp>

#endif // GFX_H

sf::Image load_image(std::string filename );    //load an image from a file
void createMask(sf::Image &image);  //create a mask for an image
