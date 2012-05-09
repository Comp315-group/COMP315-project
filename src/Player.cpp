#include "Player.h"

Player::Player(string name_, sf::Image image_){
    name = name_;
    score = 0;
    xPos = 0;
    yPos = 0;
    image = image_;
    sprite.SetImage(image);
    sprite.SetX(xPos);
    sprite.SetY(yPos);
}

string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

float Player::getTime(){
    return time;
}

void Player::resetScore(){
    score = 0;
}

void Player::resetTime(){
    time = 0;
}

void Player::incrementScore(int value){
    score+=value;

    if (score < 0)
        resetScore();
}

void Player::incrementTime(float value){
    time+=value;

    if (time < 0)
        resetTime();
}

int Player::getXPos(){
    return xPos;
}

int Player::getYPos(){
    return yPos;
}

void Player::alterX(int x){
    xPos+=x;
    sprite.SetX(xPos);
}

void Player::alterY(int y){
    yPos+=y;
    sprite.SetY(yPos);
}

void Player::move(int newX, int newY)
{
    xPos = newX;
    yPos = newY;
    sprite.SetX(newX);
    sprite.SetY(newY);
}

sf::Image Player::getImage(){
    return image;
}

void Player::setImage(sf::Image image_){
    image = image_;
    sprite.SetImage(image);
}

sf::Sprite Player::getSprite(){
    return sprite;
}

void Player::setSprite(sf::Sprite sprite_){
    sprite = sprite_;
}

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
