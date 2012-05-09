#ifndef GAMETIMER_H_INCLUDED

/**
    Keeps track of how long players have been playing for
*/

#define GAMETIMER_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class GameTimer{

    sf::Clock timer;//it is a clock timer 
    float _time;//keepps the time

public:
    GameTimer(float time) {_time = time;}
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
    return _time - timer.GetElapsedTime();
}

#endif // GAMETIMER_H_INCLUDED
