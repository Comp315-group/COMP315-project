#include "Player.h"

Player::Player(string name_, sf::Image image_){
    //initializes the player name to the given name
    name = name_;

    //sets the initial score to 0
    score = 0;

    //sets the player's x position to 0
    xPos = 0;

    //sets the player's y position to 0
    yPos = 0;

    //sets the player's image to the specified Image
    image = image_;

    //generates the Sprite from the Image
    sprite.SetImage(image);

    //sets the Sprite's x and y co-ordinates
    sprite.SetX(xPos);
    sprite.SetY(yPos);
}

/*
    returns the player name
*/
string Player::getName() const{
    return name;
}

/*
    returns the player score
*/
int Player::getScore() const{
    return score;
}

/*
    resets the player score to 0
*/
void Player::resetScore(){
    score = 0;
}

/*
    increments the player score by the specified value
*/
void Player::incrementScore(int value){
    score+=value;

    //resets the score to 0 if the score is a negative value
    if (score < 0)
        resetScore();
}

/*
    returns the player's x co-ordinate
*/
int Player::getXPos(){
    return xPos;
}

/*
    returns the player's y co-ordinate
*/
int Player::getYPos(){
    return yPos;
}

/*
    alters the player's x co-ordinate by the specified value
*/
void Player::alterX(int x){
    xPos+=x;
    sprite.SetX(xPos);
}

/*
    alters the player's y co-ordinate by the specified value
*/
void Player::alterY(int y){
    yPos+=y;
    sprite.SetY(yPos);
}

/*
    sets the player's x and y co-ordinates to the spefied values
    as well as altering the player's sprite to the new co-ordinates
*/
void Player::move(int newX, int newY)
{
    xPos = newX;
    yPos = newY;
    sprite.SetX(newX);
    sprite.SetY(newY);
}

/*
    returns the player's image
*/
sf::Image Player::getImage(){
    return image;
}

/*
    sets the player image to the specified image
*/
void Player::setImage(sf::Image image_){
    image = image_;
    sprite.SetImage(image);
}

/*
    returns the player's sprite
*/
sf::Sprite Player::getSprite() const{
    return sprite;
}

/*
    sets the player sprite to the specified sprite
*/
void Player::setSprite(sf::Sprite sprite_){
    sprite = sprite_;
}

//get player time
float Player::getTime(){
    return time;
}

//reset player time
void Player::resetTime(){
    time = 0;
}

//add to player time
void Player::incrementTime(float value){
    time+=value;

    if (time < 0)
     resetTime();
}
/*
    changes the player's avatar to the specified avatar Image
*/
void Player::changeAvatar(sf::Image new_avatar)
{
    avatar = new_avatar;
    avatar_sprite.SetImage(avatar);

    //for now, the avatar's location is hard-coded to be first place on the win screen
    avatar_sprite.SetX(455);
    avatar_sprite.SetY(180);
}

Player::~Player()
{
    //dtor
}
