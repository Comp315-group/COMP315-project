#ifndef GAMETIMER_H_INCLUDED

#define GAMETIMER_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class GameTimer{

    sf::Clock timer;
    float _time;

public:

    void start();
    float getTimeRemaining();
};

void GameTimer::start()

{
    timer.Reset();
}

float GameTimer::getTimeRemaining()

{
    return (timer.GetElapsedTime());
}

#endif // GAMETIMER_H_INCLUDED
