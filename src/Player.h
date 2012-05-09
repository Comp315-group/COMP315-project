#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.HPP>

using namespace std;

class Player{
    private:
        //player time
        float time;

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
        //Player constructor using string and image as inputs
        Player(string name_, sf::Image image_);

        //returns the player name
        string getName() const;

        //gets the time of this player
        float getTime();

        //reset player time
        void resetTime();

        //increase time
        void incrementTime(float time);

        //sets the player name to the specified string value
        void setName(string s) { name = s;};

        //returns the player score
        int getScore() const;

        //resets the player score to 0
        void resetScore();

        //increases the player score by the specified value
        void incrementScore(int value);

        //return the player x co-ordinate
        int getXPos();

        //return the player y co-ordinate
        int getYPos();

        //changes the x co-ordinate by the specified value
        void alterX(int x);

        //changes the y co-ordinate by the specified value
        void alterY(int y);

        //changes the x and y co-ordinates to the specified values
        void move(int newX, int newY);

        //returns the player image
        sf::Image getImage();

        //sets the player image to the specified image
        void setImage(sf::Image image_);

        //returns the player sprite
        sf::Sprite getSprite() const;

        //sets the player sprite to the specified sprite
        void setSprite(sf::Sprite sprite);

        //changes the player avatar to the specified image
        void changeAvatar(sf::Image new_avatar);

        //returns the player avatar
        sf::Sprite getAvatar() const {return avatar_sprite;};

        //deletes the Player object
        ~Player();
};

#endif // PLAYER_H
