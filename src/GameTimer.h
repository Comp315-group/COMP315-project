#ifndef GAMETIMER_H_INCLUDED

/**
    Keeps track of how long players have been playing for
*/

#define GAMETIMER_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class GameTimer{

    sf::Clock timer;
    float _time;

public:
    GameTimer(float time) {_time = time;}
    void start();
    float getTimeRemaining();
};

void GameTimer::start()

{
    timer.Reset();
}

float GameTimer::getTimeRemaining()
{
    return _time - timer.GetElapsedTime();
}

#endif // GAMETIMER_H_INCLUDED
