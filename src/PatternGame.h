#ifndef PATTERNGAME_H
#define PATTERNGAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <string>

#endif // PATTERNGAME_H

using namespace sf;
using namespace std;

class PatternGame
{
    public:
                PatternGame();
                void draw(RenderWindow &gameWindow);
                void drawText(RenderWindow &gameWindow);
                bool gameOver();
                void correct(int,int);

    private:
                bool patterngameOver;

                vector<string> * pattern; //string for the pattern
                vector<string> * displaypattern; //string for the pattern to fill
                int num;
                string name;
                string display;

                vector<Sprite> * SpriteDisplay;
                vector<Image> *  ImagesD;
                vector<Sprite> * SpritePattern;
                vector<Image> *  ImagesP;

                //just sets the strings
                vector<string> * set_display(int);
                vector<string> * set_Pattern();
                void setnum(int);
                void swapdisplay();
                void swappattern();
                string oddpicture(int);
                int X(int);
                int Xpos(int);

                void set_correctString(int);
                void load();
};

//Constructor for PatternGame
PatternGame :: PatternGame()
{
    patterngameOver = false;
    display = "";

    displaypattern = set_display(1 + rand() % 16);
     pattern = set_Pattern();

        swapdisplay();
        swappattern();
        load();
}

//loads the images to the sprite
void PatternGame :: load()
{

       SpritePattern = new vector<Sprite>(9);
        ImagesP = new vector<Image> (9);

        SpriteDisplay = new vector<Sprite>(3);
        ImagesD = new vector<Image> (3);

       Image image;
    for(int i = 0; i < 9; i++){
        image.LoadFromFile("resource/img/pattern/"  + pattern ->at(i) + ".jpg");
        ImagesP->at(i) = image;

        Sprite s;
        s.SetImage(ImagesP->at(i));
        s.SetPosition(X(i),40);
        s.Resize(100,150);

        SpritePattern->at(i) = s;

        }


    for(int i = 0; i < 3; i++){
         image.LoadFromFile("resource/img/pattern/"  + displaypattern->at(i) + ".jpg");
        ImagesD->at(i) = image;

        Sprite s;
        s.SetImage(ImagesD->at(i));
        s.SetPosition(Xpos(i),400);
        s.Resize(200,200);

        SpriteDisplay->at(i) = s;
    }

}


//draws the images and the string to the screen
void PatternGame :: draw(sf::RenderWindow &gameWindow)
{

        for(int i = 0; i < 9; i++){
       
        gameWindow.Draw(SpritePattern -> at(i));
        }

       for(int i = 0; i < 3; i++){
          gameWindow.Draw(SpriteDisplay -> at(i));

        }

        sf :: String Text;
        string findword = " Finish the pattern ";

        Text.SetText(findword);
        Text.SetSize(100);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(100,210);
        gameWindow.Draw(Text);


        drawText(gameWindow);
}

//draws the string to the screen
void PatternGame :: drawText(sf::RenderWindow &gameWindow)
{
        sf::String Text;
        Text.SetText(display);
        Text.SetSize(100);
        Text.SetColor(sf::Color ::Blue);
        Text.SetPosition(120,600);
        gameWindow.Draw(Text);
}

//gets the coordinates of the click and checks it
void PatternGame :: correct(int x, int y)
{
        if((x >= 190 && x <=390) && (y >=400 && y <= 600)){
        set_correctString(0);
    }
    else if((x >= 400 && x <= 600) && (y >=400 && y <= 600)){
         set_correctString(1);
    }
     else if((x >= 610 && x <= 810) && (y >=400 && y <= 600)){
         set_correctString(2);
    }
}

//checks if the click is correct
void PatternGame :: set_correctString(int i)
{
    if(displaypattern -> at(i) == name){
    display = "     CORRECT";
    patterngameOver = true;
    }
    else{
        display = "Wrong try again";
    }
}

//checks if the game is over
bool PatternGame :: gameOver()
{
    return patterngameOver;
}

//if the pattern is 2 it fills the display 
//with the another picture
string PatternGame :: oddpicture(int i)
{
    switch(i){
                  case 1:
                    return "E";
         case 2:
                    return "3";
         case 3:
                    return "Rectangle";
         case 4:
                    return "Ant";
         case 5:
                    return "2";
         case 6:
                    return "A";
        default:
                    return NULL;
    }
}

//if the number is only 2 then it sets the number to 
//another number
void PatternGame :: setnum(int n)
{
    num = n;
}

//changes the postion of the wrong one
void PatternGame :: swappattern()
{
    int i = rand() % 8;
    name = pattern -> at(i);
    pattern -> at(i) = "_";
}

//changes the pattern in the display vector
 void PatternGame :: swapdisplay()
 {

            if(num != 3){
                displaypattern->at(num) = oddpicture(1 + rand() % 5);
            }


            int i = 1 + rand() % 2;
            int j = rand() % 2;

            string temp =  displaypattern -> at(i);
            displaypattern -> at(i) = displaypattern -> at(j);
            displaypattern -> at(j) = temp;
 }

//fills the vector with a random set
vector<string> * PatternGame :: set_display(int i)
{
         vector<string> * d = new  vector<string>;

switch(i){
      case 1:
                    d -> push_back("C");
                    d -> push_back("A");
                    d -> push_back("C");
                    setnum(2);
                    return d;
        case 2:
                    d -> push_back("Circle");
                    d -> push_back("Square");
                    d -> push_back("Square");
                    setnum(2);
                    return d;
        case 3:
                    d -> push_back("Diamond");
                    d -> push_back("Pentagon");
                    d -> push_back("Triangle");
                    setnum(3);
                    return d;
        case 4:
                    d -> push_back("Diamond");
                    d -> push_back("Diamond");
                    d -> push_back("Circle");
                    setnum(0);
                    return d;
        case 5:
                    d -> push_back("A");
                    d -> push_back("B");
                    d -> push_back("C");
                    setnum(3);
                    return d;
        case 6:
                    d -> push_back("5");
                    d -> push_back("6");
                    d -> push_back("7");
                    setnum(3);
                    return d;
        case 7:
                    d -> push_back("5");
                    d -> push_back("Pentagon");
                    d -> push_back("5");
                    setnum(2);
                    return d;
        case 8:
                    d -> push_back("Airplane");
                    d -> push_back("Boat");
                    d -> push_back("Train");
                    setnum(3);
                    return d;
        case 9:
                    d -> push_back("Starfish");
                    d -> push_back("Jellyfish");
                    d -> push_back("Sea horse");
                    setnum(3);
                    return d;
        case 10:
                    d -> push_back("Circle");
                    d -> push_back("Square");
                    d -> push_back("Square");
                    setnum(2);
                    return d;
        case 11:
                    d -> push_back("Blue Hat");
                    d -> push_back("Green Hat");
                    d -> push_back("Yellow Hat");
                    setnum(3);
                    return d;
        case 12:
                    d -> push_back("Spider");
                    d -> push_back("Ant");
                    d -> push_back("Worm");
                    setnum(3);
                    return d;
        case 13:
                    d -> push_back("2");
                    d -> push_back("3");
                    d -> push_back("4");
                    setnum(3);
                    return d;
        case 14:
                    d -> push_back("Blue");
                    d -> push_back("Blue");
                    d -> push_back("Green");
                    setnum(1);
                    return d;
        case 15:
                    d -> push_back("Lemon");
                    d -> push_back("Strawberry");
                    d -> push_back("Banana");
                    setnum(3);
                    return d;
       case 16:
                    d -> push_back("Fluttershy");
                    d -> push_back("Pinkiepie");
                    d -> push_back("Rainbowdash");
                    setnum(3);
                    return d;
    default:
                return NULL;
}

}

//fills the rest of the pattern
vector<string> * PatternGame :: set_Pattern()
{
    vector<string> * p = new vector<string>;

    for(int i = 0; i < 3; i++){
        p->push_back(displaypattern->at(i));
    }
    int j = 0;
    for(int i = 3; i < 6; i++){
        p->push_back(displaypattern->at(j));
        j++;
    }
    j = 0;
    for(int i = 6; i < 9; i++){
        p->push_back(displaypattern->at(j));
        j++;
    }

    return p;
}

//sets the x coordinates of the pattern to draw
int PatternGame:: X(int i)
{

    switch(i){
        case 0:
                    return 20;
         case 1:
                    return 130;
        case 2:
                    return 240;
         case 3:
                    return 350;
         case 4:
                    return 460;
        case 5:
                    return 570;
         case 6:
                    return 680;
         case 7:
                    return 790;
        case 8:
                    return 900;

        default:
                    return NULL;
    }
}

//sets the x coordinates of the display to draw
int PatternGame :: Xpos(int i)
{
    switch(i){
        case 0:
                    return 190;
         case 1:
                    return 400;
        case 2:
                    return 610;
        default:
                    return NULL;
    }
}


