#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <string>

#endif //  MEMORYGAME_H

using namespace std;
using namespace sf;

class MemoryGame{

    public:
        MemoryGame();
        bool gameOver();
        void draw(RenderWindow &gameWindow);
        void update(int xpos, int ypos, RenderWindow &gameWindow);

    private:
        vector <string> * generateGrid(int value);
        void randomize();
        int X(int i);
        int Y(int i);

        int xPos;
        int yPos;
        int revealA;
        int revealB;
        int hiddenTiles;
        int noRevealed;
        bool memoryGameOver;
        size_t found;
        vector <string> * grid;

        vector<Sprite> * SpriteImages;
        vector<Sprite> * SpriteBacks;
        vector<Sprite> * SpriteBlanks;

        vector<Image> * Images;
        vector<Image> * Backs;
        vector<Image> * Blanks;
};

MemoryGame::MemoryGame(){
    memoryGameOver = false;
    noRevealed = 0;
    revealA = -1;
    revealB = -1;
    hiddenTiles = 16;
    grid = generateGrid((rand()% 3)+1);
    randomize();

    SpriteImages = new vector<Sprite> (16);
    SpriteBacks = new vector<Sprite> (16);
    SpriteBlanks = new vector<Sprite> (16);

    Images = new vector<Image> (16);
    Backs = new vector<Image> (16);
    Blanks = new vector<Image> (16);

    Image image;

    Image back;
    back.LoadFromFile("resource/img/memory/back.png");

    Image blank;
    blank.LoadFromFile("resource/img/memory/blank.png");

    int count = 0;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            image.LoadFromFile("resource/img/memory/" + grid->at(count) + ".png");
            Images->at(count) = image;
            Backs->at(count) = back;
            Blanks->at(count) = blank;

            Sprite s;
            s.SetImage(Images->at(count));
            s.SetPosition(X(i),Y(j));
            s.Resize(75,75);
            SpriteImages->at(count) = s;

            Sprite covered;
            covered.SetImage(Backs->at(count));
            covered.SetPosition(X(i),Y(j));
            covered.Resize(75,75);
            SpriteBacks->at(count) = covered;

            Sprite blank_;
            blank_.SetImage(Blanks->at(count));
            blank_.SetPosition(X(i),Y(j));
            blank_.Resize(75,75);
            SpriteBlanks->at(count) = blank_;

            count++;
        }
    }
}

bool MemoryGame::gameOver(){
    return memoryGameOver;
}

int MemoryGame::X(int i){
    switch(i){
        case 0:
            return 375;
        case 1:
            return 450;
        case 2:
            return 525;
        case 3:
            return 600;
        case 4:
            return 675;
        default:
            return NULL;
    }
}

int MemoryGame::Y(int j){
    switch(j){
        case 0:
            return 275;
        case 1:
            return 350;
        case 2:
            return 425;
        case 3:
            return 500;
        case 4:
            return 575;
        default:
            return NULL;
    }
}

void MemoryGame::update(int xpos, int ypos, RenderWindow &gameWindow){
    if(xpos>=375&&xpos<=450){
        if(ypos>=275&&ypos<=350){
            if((grid->at(0)).size()!=0 && revealA!=0){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=0;
                    else
                        revealB=0;
                }
            }
        }
        else if(ypos>=350&&ypos<=425){
            if((grid->at(1)).size()!=0  && revealA!=1){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=1;
                    else
                        revealB=1;
                }
            }
        }
        else if(ypos>=425&&ypos<=500){
            if((grid->at(2)).size()!=0 && revealA!=2){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=2;
                    else
                        revealB=2;
                }
            }
        }
        else if(ypos>=500&&ypos<=575){
            if((grid->at(3)).size()!=0 && revealA!=3){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=3;
                    else
                        revealB=3;
                }
            }
        }
    }

    else if(xpos>=450&&xpos<=525){
        if(ypos>=275&&ypos<=350){
            if((grid->at(4)).size()!=0 && revealA!=4){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=4;
                    else
                        revealB=4;
                }
            }
        }
        else if(ypos>=350&&ypos<=425){
            if((grid->at(5)).size()!=0 && revealA!=5){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=5;
                    else
                        revealB=5;
                }
            }
        }
        else if(ypos>=425&&ypos<=500){
            if((grid->at(6)).size()!=0 && revealA!=6){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=6;
                    else
                        revealB=6;
                }
            }
        }
        else if(ypos>=500&&ypos<=575){
            if((grid->at(7)).size()!=0 && revealA!=7){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=7;
                    else
                        revealB=7;
                }
            }
        }
    }

    else if(xpos>=525&&xpos<=600){
        if(ypos>=275&&ypos<=350){
            if((grid->at(8)).size()!=0 && revealA!=8){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=8;
                    else
                        revealB=8;
                }
            }
        }
        else if(ypos>=350&&ypos<=425){
            if((grid->at(9)).size()!=0 && revealA!=9){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=9;
                    else
                        revealB=9;
                }
            }
        }
        else if(ypos>=425&&ypos<=500){
            if((grid->at(10)).size()!=0 && revealA!=10){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=10;
                    else
                        revealB=10;
                }
            }
        }
        else if(ypos>=500&&ypos<=575){
            if((grid->at(11)).size()!=0 && revealA!=11){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=11;
                    else
                        revealB=11;
                }
            }
        }
    }

    else if(xpos>=600&&xpos<=675){
        if(ypos>=275&&ypos<=350){
            if((grid->at(12)).size()!=0 && revealA!=12){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=12;
                    else
                        revealB=12;
                }
            }
        }
        else if(ypos>=350&&ypos<=425){
            if((grid->at(13)).size()!=0 && revealA!=13){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=13;
                    else
                        revealB=13;
                }
            }
        }
        else if(ypos>=425&&ypos<=500){
            if((grid->at(14)).size()!=0 && revealA!=14){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=14;
                    else
                        revealB=14;
                }
            }
        }
        else if(ypos>=500&&ypos<=575){
            if((grid->at(15)).size()!=0 && revealA!=15){
                if(noRevealed<2){
                    noRevealed++;
                    if(revealA<0)
                        revealA=15;
                    else
                        revealB=15;
                }
            }
        }
    }

    draw(gameWindow);

    if(noRevealed==2){
        found = (grid->at(revealA)).find(grid->at(revealB));
        if((int)found==0){
            grid->at(revealA) = "";
            grid->at(revealB) = "";
            hiddenTiles = hiddenTiles -2;
        }

        revealA = -1;
        revealB = -1;
        noRevealed = 0;
    }

    if(hiddenTiles==0)
       memoryGameOver = true;
}

void MemoryGame::draw(sf::RenderWindow &gameWindow)
{
    int count = 0;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(count==revealA || count==revealB)
                gameWindow.Draw(SpriteImages -> at(count));
            else if((grid->at(count)).size()==0)
                gameWindow.Draw(SpriteBlanks -> at(count));
            else
                gameWindow.Draw(SpriteBacks -> at(count));
            count++;
        }
    }

    sf :: String Text;
    string header = " Uncover all the tiles ";

    Text.SetText(header);
    Text.SetSize(85);
    Text.SetColor(sf::Color :: Red);
    Text.SetPosition(10,50);
    gameWindow.Draw(Text);
}

vector<string>* MemoryGame::generateGrid(int value){
    vector<string> *temp = new vector<string>;

    switch(value){
        case 1:{
            temp->push_back("A");
            temp->push_back("C");
            temp->push_back("D");
            temp->push_back("C");

            temp->push_back("H");
            temp->push_back("F");
            temp->push_back("G");
            temp->push_back("E");

            temp->push_back("A");
            temp->push_back("B");
            temp->push_back("E");
            temp->push_back("B");

            temp->push_back("D");
            temp->push_back("F");
            temp->push_back("H");
            temp->push_back("G");

            return temp;
        }

        case 2:{
            temp->push_back("cow");
            temp->push_back("elephant");
            temp->push_back("elephant");
            temp->push_back("zebra");

            temp->push_back("goat");
            temp->push_back("owl");
            temp->push_back("hippo");
            temp->push_back("penguin");

            temp->push_back("penguin");
            temp->push_back("pig");
            temp->push_back("zebra");
            temp->push_back("pig");

            temp->push_back("owl");
            temp->push_back("cow");
            temp->push_back("hippo");
            temp->push_back("goat");

            return temp;
        }

        case 3:{
            temp->push_back("apple");
            temp->push_back("balloons");
            temp->push_back("eye");
            temp->push_back("ghost");

            temp->push_back("eye");
            temp->push_back("cake");
            temp->push_back("ghost");
            temp->push_back("balloons");

            temp->push_back("flower");
            temp->push_back("star");
            temp->push_back("fish");
            temp->push_back("fish");

            temp->push_back("star");
            temp->push_back("cake");
            temp->push_back("flower");
            temp->push_back("apple");

            return temp;
        }




        default:
            return NULL;
    }
}

void MemoryGame::randomize(){
    for(int i=0;i<50;i++){
        string temp;
        int a = rand()%16;
        int b = rand()%16;

        temp = grid->at(a);
        grid->at(a) = grid->at(b);
        grid->at(b) = temp;
    }
}

