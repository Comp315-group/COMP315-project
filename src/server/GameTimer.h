#ifndef GAMETIMER_H_INCLUDED

/**
    Keeps track of how long players have been playing for
*/

#define GAMETIMER_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class GameTimer{

    //timer object
    sf::Clock timer;
    //the total time that this timer will run for
    float _time;

public:
    GameTimer(float time) {_time = time;} //constructor accepts timer duration
    void start();
    float getTimeRemaining();
};

//start the timer
void GameTimer::start()
{
    timer.Reset();
}

//get remaining time
float GameTimer::getTimeRemaining()
{
    return _time - timer.GetElapsedTime();
}

#endif // GAMETIMER_H_INCLUDED
