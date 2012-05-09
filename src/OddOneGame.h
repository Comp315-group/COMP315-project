#ifndef ODDONEGAME_H
#define ODDONEGAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <string>

#endif // ODDONEGAME_H

using namespace sf;
using namespace std;

class OddOneGame
{

    public:
     OddOneGame();
     void draw(sf::RenderWindow &gameWindow);
     void drawText(sf::RenderWindow &gameWindow);
     bool gameOver();
     void correct(int, int );

private:
     vector<string> * oddoneout;
     string word;
     string display;

     vector<Sprite> * SpriteImages;
     vector<Image> * Images;

     void swap();
     vector<string> * setstring(int num);

     bool OddOneGameOver;

     int X(int);
     void set_correctString(int);
     void load();

};

//gets the Coordinates of the click and sends it to the matching method    
void OddOneGame :: correct(int x, int y)
{
    if((x >= 10 && x <=250) && (y >=250 && y <= 500)){
        set_correctString(0);
    }
    else if((x >= 260 && x <= 500) && (y >=250 && y <= 500)){
         set_correctString(1);
    }
     else if((x >= 510 && x <= 750) && (y >=250 && y <= 500)){
         set_correctString(2);
    }
     else if((x >= 770 && x <= 1000) && (y >=250 && y <= 500)){
         set_correctString(3);
    }

}

//Constructor of Odd_One_Out 
OddOneGame::OddOneGame()
{
    OddOneGameOver = false;
     oddoneout = setstring(1 + (rand() % 15));
     swap();
     load();
     
     display = "";

}

//Draws the images and strings to the screen 
void OddOneGame::draw(sf::RenderWindow &gameWindow)
{
       for(int i = 0; i < 4; i++){
              gameWindow.Draw(SpriteImages -> at(i));
        }

        sf :: String Text;
        string findword = " Find the Odd One Out ";

        Text.SetText(findword);
        Text.SetSize(85);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(50,50);
        gameWindow.Draw(Text);

        drawText(gameWindow);


}

//this gets the images to be loaded to the screen
void OddOneGame :: load(){
  SpriteImages = new vector<Sprite> (4);
  Images = new vector<Image>(4);

    Image image;
    for(int i = 0; i < 4; i++){
        image.LoadFromFile("resource/img/odd/" + oddoneout->at(i) + ".jpg");
        Images ->at(i) = image;

        Sprite s;
        s.SetImage(Images ->at(i));
        s.SetPosition(X(i),250);
        s.Resize(235,250);
        SpriteImages->at(i) = s;
        }

}

//draws the text to the screen
void OddOneGame::drawText(sf::RenderWindow &gameWindow)
{
    sf::String Text;
        Text.SetText(display);
        Text.SetSize(90);
        Text.SetColor(sf::Color :: Blue);
        Text.SetPosition(150,550);
        gameWindow.Draw(Text);
}

//gets the x postion to draw to the screen
int OddOneGame :: X(int i)
{
 switch(i){
                    case 0:
                                return 10;
                    case 1:
                                return 260;
                    case 2:
                                return 515;
                    case 3:
                                return 770;
                    default:
                                return NULL;
    }
}

//checks if the game is over
bool OddOneGame::gameOver()
{
    return OddOneGameOver;
}

//switches the images about in the vector
void OddOneGame:: swap()
{
        int num = rand()%4;
        string temp = oddoneout->at(3);
        oddoneout->at(3) = oddoneout->at(num);
        oddoneout->at(num) = temp;
}

//looks if the area that was clicked is correct or wrong 
void OddOneGame :: set_correctString(int i)
{
    if(oddoneout -> at(i) == word){
    display = "     CORRECT";
    OddOneGameOver = true;
    }
    else{
        display = "Wrong try again";
    }
}

//Sets the vector to diffrent image names
vector<string> * OddOneGame:: setstring(int num)
{
    vector<string> * total = new vector<string>;

    switch(num){
              case 1:
                        total->push_back("A");
                        total->push_back("B");
                        total->push_back("C");
                        total->push_back("8");
                        word = "8";
                        return total;
               case 2:
                         total->push_back("Circle");
                        total->push_back("Square");
                        total->push_back("Triangle");
                        total->push_back("H");
                        word = "H";
                        return total;;
               case 3:
                        total->push_back("1");
                        total->push_back("2");
                        total->push_back("3");
                        total->push_back("Diamond");
                        word = "Diamond";
                        return total;
                case 4:
                       total->push_back("Giraffe");
                        total->push_back("Lion");
                        total->push_back("Zebra");
                        total->push_back("Duck");
                        word = "Duck";
                        return total;
                case 5:
                      total->push_back("Sheep");
                        total->push_back("Donkey");
                        total->push_back("Rabbits");
                        total->push_back("Elephant");
                        word = "Elephant";
                        return total;
                case 6:
                       total->push_back("Jelly Beans");
                        total->push_back("Sucker");
                        total->push_back("Sweet Packet");
                        total->push_back("Pineapple");
                        word = "Pineapple";
                        return total;
                case 7:
                      total->push_back("Car");
                        total->push_back("Truck");
                        total->push_back("Bus");
                        total->push_back("Airplane");
                        word = "Airplane";
                        return total;
                case 8:
                         total->push_back("Butterfly");
                        total->push_back("Bee");
                        total->push_back("Lady Bug");
                        total->push_back("Worm");
                        word = "Worm";
                        return total;
                case 9:
                      total->push_back("Apple");
                        total->push_back("Orange");
                        total->push_back("Pear");
                        total->push_back("Radish");
                        word = "Radish";
                        return total;
                case 10:
                  total->push_back("Hammer");
                        total->push_back("Spanner");
                        total->push_back("Screw Driver");
                        total->push_back("Rubber");
                        word = "Rubber";
                        return total;
                case 11:
                    total->push_back("Scissors");
                        total->push_back("Pen");
                        total->push_back("Pencil");
                        total->push_back("Horse");
                        word = "Horse";
                        return total;
                case 12:
                        total->push_back("Penguin");
                        total->push_back("Sea Horse");
                        total->push_back("Seal");
                        total->push_back("Turkey");
                        word = "Turkey";
                        return total;
                case 13:
                       total->push_back("Baseketball");
                        total->push_back("Soccer");
                        total->push_back("Tennis");
                        total->push_back("Bike");
                        word = "Bike";
                        return total;
                case 14:
                    total->push_back("Dress");
                        total->push_back("Shirt");
                        total->push_back("Shorts");
                        total->push_back("Shoes");
                        word = "Shoes";
                        return total;
                 case 15:
                        total->push_back("Aubergine");
                        total->push_back("Carrot");
                        total->push_back("Pea");
                        total->push_back("Watermelon");
                        word = "Watermelon";
                        return total;
               
                default:
                    return NULL;

        }
}
