#include "Player.h"

Player::Player(string name_, sf::Image image_){
    name = name_;
    score = 10;
    xPos = 9*32;
    yPos = 11*32;
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

void Player::resetScore(){
    score = 0;
}

void Player::incrementScore(int value){
    score+=value;
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

Player::~Player()
{
    //dtor
}
