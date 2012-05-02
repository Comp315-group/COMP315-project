#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.HPP>

using namespace std;

class Player{
    private:
        //The name of this player
        string name;
        //player score
        int score;
        //player x coordinate used in the maze game
        int xPos;
        //player y coordinate used in the maze game
        int yPos;

        //the player image, used in the mazegame
        sf::Image image;
        //the sprite created from the above image
        sf::Sprite sprite;

        //the player's portrait
        sf::Image avatar;
        //the sprite created from the above image
        sf::Sprite avatar_sprite;

    public:
        Player(string name_, sf::Image image_);
        string getName();
        void setName(string s) { name = s;};
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
        void changeAvatar(sf::Image new_avatar);
        sf::Sprite getAvatar() const {return avatar_sprite;};
        ~Player();
};

#endif // PLAYER_H
