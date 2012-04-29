#ifndef GAMETIMER_H_INCLUDED
#define GAMETIMER_H_INCLUDED

class GameTimer{

    sf::String timer_text;
    sf::Clock timer;
    float _time;

public:
    GameTimer();
    void start();
    int getTimeRemaining();
};

GameTimer::GameTimer()
{
    _time = 120.f;    //Time starts at 2 minutes

    timer_text.SetText("Time remaining : " + toString(_time) + "s");
    timer_text.SetSize(30);
    timer_text.SetColor(sf::Color ::Green);
    timer_text.SetPosition(0,600);
}

void GameTimer::start()
{
    timer.Reset();
}

int GameTimer::getTimeRemaining()
{
    return (int)(_time - timer.GetElapsedTime());
}



#endif // GAMETIMER_H_INCLUDED
