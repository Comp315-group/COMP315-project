#ifndef HIDEGAME_H
#define HIDEGAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <string>

#endif // HIDEGAME_H


class HideGame
{
    public:
                HideGame();
                void draw(sf::RenderWindow &gameWindow);
                void DrawText(sf::RenderWindow &gameWindow);
                bool gameOver();
                void correct(int,int);

    private:
                vector<string> * names;
                vector<string> * hide_seek;
                string to_find;
                string display;

                vector<string> * fill();
                vector<string> * fill_names(int);
                void swap();
                void swap_fill();

                bool hideGameOver;
                void set_correctString(int);
                int X(int);
                int Y(int);
};

HideGame :: HideGame()
{
    names = fill_names(rand() % 5);
    swap();
    hide_seek =  fill();
    hideGameOver = false;

    for(int i  = 0; i < 15; i ++){
    swap_fill();
    }

}

void HideGame :: draw(sf::RenderWindow &gameWindow)
{

 vector <Sprite> * Test = new vector<Sprite>(15);
        Image image;
        for(int i = 0; i < 15; i++){
        image.LoadFromFile("resource/img/hide/"  + hide_seek->at(i) + ".jpg");

        Sprite s;
        s.SetImage(image);
        s.SetPosition(X(i), Y(i));
        s.Resize(150,150);

        Test->at(i) = s;

        gameWindow.Draw(Test -> at(i));
        }

        sf :: String Text;
        string findword = "Click on the ";
        findword.append(to_find);
        findword.append("\n   in the grid below");

        Text.SetText(findword);
        Text.SetSize(70);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(200,10);
        gameWindow.Draw(Text);

        DrawText(gameWindow);

}

void HideGame::DrawText(sf::RenderWindow &gameWindow)
{
    sf::String Text;
    Text.SetText(display);
        Text.SetSize(70);
        Text.SetColor(sf::Color :: Blue);
        Text.SetPosition(250,650);
        gameWindow.Draw(Text);
}

int HideGame :: X(int i)
{
 switch(i){
                    case 0: case 5: case 10:
                                return 125;
                    case 1: case 6: case 11:
                                return 275;
                    case 2: case 7: case 12:
                                return 425;
                    case 3: case 8: case 13:
                                return 575;
                    case 4: case 9: case 14:
                                return 725;
                    default:
                                return NULL;
    }
}

int HideGame :: Y(int i)
{
 switch(i){
                    case 0: case 1: case 2: case 3: case 4:
                                return 200;
                    case 5: case 6: case 7: case 8: case 9:
                                return 350;
                    case 10: case 11: case 12: case 13: case 14:
                                return 500;
                    default:
                                return NULL;
    }
}

void HideGame :: swap_fill()
{
int i = rand() % 15;
int j = rand() % 15;

string temp = hide_seek->at(i);
hide_seek->at(i) = hide_seek->at(j);
hide_seek->at(j) = temp;
}

void HideGame:: swap()
{
int i = rand() % 5;
int j = rand() % 5;

string temp = names->at(i);
names->at(i) = names->at(j);
names->at(j) = temp;

}

vector<string> * HideGame:: fill_names(int num)
{

 vector<string> * complete = new vector<string>;

 switch(num){
 case 0:
            complete -> push_back("Red Star");
            complete -> push_back("Blue Star");
            complete -> push_back("Pink Star");
            complete -> push_back("Purple Star");
            complete -> push_back("Green Star");
case 1:
            complete -> push_back("Cow");
            complete -> push_back("Hen");
            complete -> push_back("Pig");
            complete -> push_back("Mouse");
            complete -> push_back("Sheep");
case 2:
            complete -> push_back("Square");
            complete -> push_back("Triangle");
            complete -> push_back("Diamond");
            complete -> push_back("Circle");
            complete -> push_back("Pentagon");
case 3:
            complete -> push_back("Apple");
            complete -> push_back("Plum");
            complete -> push_back("Pear");
            complete -> push_back("Strawberry");
            complete -> push_back("Banana");
case 4:
            complete -> push_back("Airplane");
            complete -> push_back("Car");
            complete -> push_back("Bus");
            complete -> push_back("Train");
            complete -> push_back("Boat");
 }
return complete;
}

vector<string> * HideGame:: fill()
{

 vector<string> * complete = new vector<string>;

    complete ->push_back(names->at(0));
    to_find = names->at(0);

    for(int i = 0; i < 4; i++){
     complete -> push_back(names->at(1));
    }
    for(int i = 0; i < 3; i++){
     complete -> push_back(names->at(2));
    }
    for(int i = 0; i < 2; i++){
     complete -> push_back(names->at(3));
    }
    for(int i = 0; i < 5; i++){
     complete -> push_back(names->at(4));
    }
    return complete;
}

void HideGame :: correct(int x, int y)
{

    if((x >= 125 && x <=275) && (y >=200 && y <= 350)){
        set_correctString(0);
    }
    else if((x >= 275 && x <= 425) &&(y >=200 && y <= 350)){
         set_correctString(1);
    }
     else if((x >= 425 && x <= 575) && (y >=200 && y <= 350)){
         set_correctString(2);
    }
     else if((x >= 575 && x <= 725) && (y >=200 && y <= 350)){
         set_correctString(3);
    }
       else if((x >= 725 && x <= 875) && (y >=200 && y <= 350)){
         set_correctString(4);
    }
     else if((x >= 125 && x <=275)  && (y >=350 && y <= 500)){
         set_correctString(5);
    }
     else if((x >= 275 && x <= 425) && (y >=350 && y <= 500)){
         set_correctString(6);
    }
       else if((x >= 425 && x <= 575) && (y >=350 && y <= 500)){
         set_correctString(7);
    }
     else if((x >= 575 && x <= 725) && (y >=350 && y <= 500)){
         set_correctString(8);
    }
     else if((x >= 725 && x <= 875)  && (y >=350 && y <= 500)){
         set_correctString(9);
    }
       else if((x >= 125 && x <=275)  && (y >=500 && y <= 650)){
         set_correctString(10);
    }
     else if((x >= 275 && x <= 425) && (y >=500 && y <= 650)){
         set_correctString(11);
    }
     else if((x >= 425 && x <= 575) && (y >=500 && y <= 650)){
         set_correctString(12);
    }
       else if((x >= 575 && x <= 725) && (y >=500 && y <= 650)){
         set_correctString(13);
    }
     else if((x >= 725 && x <= 875)  && (y >=500 && y <= 650)){
         set_correctString(14);
    }

}

bool HideGame::gameOver()
{
    return hideGameOver;
}

void HideGame :: set_correctString(int i)
{
    if(hide_seek -> at(i) == to_find){
    display = "   CORRECT";
    hideGameOver = true;
    }
    else{
        display = "Wrong try again";
    }
}
