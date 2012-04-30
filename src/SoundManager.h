#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SFML/Audio.HPP>

class SoundManager
{
    sf:: Music music;
    sf:: Music correct;
    sf:: Music incorrect;
    sf:: Music gameOver;

    public:
        void init();
        void playBGMusic()  {music.Play();}
        void stopBGMusic() {music.Stop();}
        void playCorrectSound() {correct.Play();}
        void playIncorrectSound() {incorrect.Play();}
        void playGameOverSound() {gameOver.Play();}
};

void SoundManager::init()
{
    if (!music.OpenFromFile("resource/sound/music.wav"))
        return ;

    if (!correct.OpenFromFile("resource/sound/correct.wav"))
     return;

     if (!gameOver.OpenFromFile("resource/sound/gameover.wav"))
     return;

     if (!incorrect.OpenFromFile("resource/sound/incorrect.wav"))
     return;
}

#endif // SOUNDMANAGER_H_INCLUDED
