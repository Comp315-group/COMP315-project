#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.HPP>
//#include "GFX.h"

using namespace std;

class Player{
    private:
        string name;
        int score;
        int xPos;
        int yPos;
        sf::Image image;
        sf::Sprite sprite;

    public:
        Player(string name_, sf::Image image_);
        string getName();
        int getScore();
        void resetScore();
        void incrementScore(int value);
        int getXPos();
        int getYPos();
        void alterX(int x);
        void alterY(int y);
        void move(int newX, int newY);
        sf::Image getImage();
        void setImage(sf::Image image_);
        sf::Sprite getSprite();
        void setSprite(sf::Sprite sprite);
        ~Player();
};

#endif // PLAYER_H
