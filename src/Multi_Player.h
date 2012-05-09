#ifndef MULTI_PLAYER_H
#define MULTI_PLAYER_H

#include <SFML/Graphics.HPP>
#include "Player.h"
#include <vector>
#include "GFX.h"
#include <iostream>
#include "Game.h"

struct Multi_Player
{
    vector <Player * > * place;
    int count;

    Multi_Player(int i);
    int get_current_player();
    bool end_of_players();
    void Update_Score(Player * &);
    void print();

};

void Multi_Player :: print(){

for(int i = 0; i < place->size(); i++){
    cout << place->at(i)->getName() << " " << place->at(i) ->getScore() << endl;
}

}

void Multi_Player :: Update_Score( Player * &t){
    place->at(count) = t;
}

Multi_Player :: Multi_Player(int i){
    place = new vector <Player * >;
    count = 0;

    for(int j = 0; j < i; j++){
        place->push_back(new Player("lunch", load_image("resource/img/player.bmp")));
    }
}

bool Multi_Player :: end_of_players(){
return count == place->size();
}

int Multi_Player ::get_current_player(){
  return count++;
}




#endif // MULTI_PLAYER_H
