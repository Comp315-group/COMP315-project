#ifndef GAMETIMER_H_INCLUDED

#define GAMETIMER_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class GameTimer{

    sf::Clock timer;//it is a clock timer 
    float _time;//keepps the time

public:

    void start();
    float getTimeRemaining();
};

//Makes the clock zero
void GameTimer::start()

{
    timer.Reset();
}

//gets the time that lasped from starting time
float GameTimer::getTimeRemaining()

{
    return (timer.GetElapsedTime());
}

#endif // GAMETIMER_H_INCLUDED
