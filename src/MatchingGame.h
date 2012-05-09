#ifndef MATCHINGGAME_H
#define MATCHINGGAME_H

#include <vector>
#include <string>
#include <SFML/Window.hpp>

#endif // MATCHINGGAME_H

class MatchingGame
{
    public:
                MatchingGame();
                void draw(sf::RenderWindow &gameWindow);
                void drawText(sf::RenderWindow &gameWindow);

                bool gameOver();
                void correct(int, int );
    private:
                int Number_to_Find;
                vector<bool> * Number_bool;
                vector <int> * Number;
                string display;

                vector<Sprite> * Test;
                vector<Image> *  Images;
                Sprite s;
                Image t;

                int random_number();
                void fill();
                void swap();
                string get_char_number(int num);
                int X(int);

                bool MatchingGameOver;
                void set_correctString(int);
                void load();

};

//Constructor for MatchingGame
MatchingGame :: MatchingGame()
{
        MatchingGameOver = false;
        display = "";

        Number_to_Find = random_number();
        Number_bool = new vector<bool>(11, true);
        Number = new vector<int>;
        fill();
        swap();
        swap();
        load();
}

//gets the coordinates of the of the click 
//checks it 
void MatchingGame :: correct(int x, int y)
{

    if((x >= 40 && x <=260) && (y >=375 && y <= 590)){
        set_correctString(0);
    }
    else if((x >= 280 && x <= 500) && (y >=375 && y <= 590)){
         set_correctString(1);
    }
     else if((x >= 520 && x <= 740) && (y >=375 && y <= 590)){
         set_correctString(2);
    }
     else if((x >= 760 && x <= 980) && (y >=375 && y <= 590)){
         set_correctString(3);
    }

}

//checks if the string is correct
void MatchingGame :: set_correctString(int i)
{
    if(Number -> at(i) == Number_to_Find){
    display = "   CORRECT";
    MatchingGameOver = true;
    }
    else{
        display = "Wrong try again";
    }
}

//draws the images to the screen
void MatchingGame :: draw(sf::RenderWindow &gameWindow)
{

        for(int i = 0; i < 4; i++){
        gameWindow.Draw(Test -> at(i));
        }

        gameWindow.Draw(s);

        sf :: String Text;
        string findword = "Match the number with the word";
         Text.SetText(findword);
        Text.SetSize(60);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(100,220);
        gameWindow.Draw(Text);

        drawText(gameWindow);

}

//loads the images to the sprite
void MatchingGame :: load(){
     Test = new vector<Sprite>(4);
      Images = new vector<Image> (4);

       Image image;
    for(int i = 0; i < 4; i++){
        image.LoadFromFile("resource/img/matching/Words/" +get_char_number(Number->at(i))+ ".jpg" );
        Images->at(i) = image;

        Sprite s;
        s.SetImage(Images->at(i));
        s.SetPosition(X(i),370);
        s.Resize(220,220);
        Test->at(i) = s;

        }

        t.LoadFromFile("resource/img/matching/Numbers/" + get_char_number(Number_to_Find) + ".jpg");
        s.SetImage(t);
        s.SetPosition(400,10);
        s.Resize(200,200);
}

//draws the images to the screen 
void MatchingGame :: drawText(sf::RenderWindow &gameWindow)
{
        sf::String Text;
        Text.SetText(display);
        Text.SetSize(100);
        Text.SetColor(sf::Color ::Blue);
        Text.SetPosition(150,600);
        gameWindow.Draw(Text);
}

//changes the number to a char
string MatchingGame :: get_char_number(int num)
{
    char k = num + 48;
    if(k == ':'){
        return "10";
    }
            string j = "";
            j.append(1,k);
            return j;

}

//checks if the game is over 
bool MatchingGame :: gameOver()
{
return MatchingGameOver;
}

//fills the rest of the string with random numbers
void MatchingGame :: fill()
{

   Number_bool ->at(Number_to_Find) = false;

    for(int i = 0; i < 3; i ++){
        int j = random_number();
        if(Number_bool -> at(j) == true){
              Number_bool -> at(j) =  false;
        }
        else{
                --i;
        }
    }

    for(int i =0 ; i < 11; i ++){
            if(Number_bool->at(i) == false){
                Number -> push_back(i);
            }
    }

}

//returns random numbers
int MatchingGame :: random_number()
{
    return rand() % 11;
}

//Switches the numbers in the vector
void MatchingGame :: swap()
{
    int i = rand() % 4;
    int j = rand() % 4;

    int temp = Number ->at(i);
    Number->at(i) = Number ->at(j);
    Number ->at(j) = temp;
}

//sets the x coordinates
int MatchingGame:: X(int i)
{
 switch(i){
                    case 0:
                                return 40;
                    case 1:
                                return 280;
                    case 2:
                                return 520;
                    case 3:
                                return 760;
                    default:
                                return NULL;
    }
}



