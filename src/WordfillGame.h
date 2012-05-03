#ifndef WORDFILLGAME_H
#define WORDFILLGAME_H
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#endif // WORDFILLGAME_H

using namespace sf;
using namespace std;

class WordfillGame
{
    public:
                WordfillGame();
                string display;
                void draw(sf::RenderWindow &gameWindow);
                 void drawText(sf::RenderWindow &gameWindow);

                 bool gameOver();
                void correct(int, int );
    private:
                vector <char> * Word_complete;
                vector <char> * random_letters;
                string Word;
                int size;
                char out;
                char other;

                vector<Sprite> * Display;
                vector<Image> * ImageT;
                vector<Sprite> * wrong_ones;
                vector<Image> * Images;
                Sprite pic;
                Image picture;

                string random_words();
                vector<char> * fill_Word_complete();
                vector<char> * fill_random_letters();
                char to_fill();

                bool WordfillGameOver;
                void set_correctString(int);
                int X(int i);
                string schange(char);
                void load();



};

WordfillGame::WordfillGame()
{

    Word = random_words();
    size = Word.length();
    Word_complete = fill_Word_complete();
    random_letters = fill_random_letters();
    WordfillGameOver = false;
    load();
    display = "";
}

bool WordfillGame :: gameOver()
{
return WordfillGameOver;
}

void WordfillGame :: correct(int x, int y)
{

    if((x >= 320&& x <=500) && (y >=400 && y <= 600)){
        set_correctString(0);
    }
    else if((x >= 520 && x <= 720) && (y >=400 && y <= 600)){
         set_correctString(1);
    }

}

void WordfillGame :: set_correctString(int i)
{
    if(random_letters -> at(i) == out){
    display = "   CORRECT";
    WordfillGameOver = true;
    }
    else{
        display = "Wrong try again";
    }
}


void WordfillGame :: load(){
    Display = new vector<Sprite>(3);
    ImageT = new vector<Image>(3);

    wrong_ones = new vector<Sprite>(2);
    Images = new vector<Image>(2);

    Image image;

    for(int i = 0; i < 3; i++){
          image.LoadFromFile("resource/img/Wordfill/"  + schange(Word_complete->at(i)) + ".png");
           ImageT->at(i) = image;

        Sprite s;
        s.SetImage(ImageT->at(i));
        s.SetPosition(X(i),50);
        s.Resize(200,200);

        Display->at(i) = s;

    }

    for(int i = 0; i < 2; i++){
      image.LoadFromFile("resource/img/Wordfill/"  + schange(random_letters->at(i)) + ".png");
      Images -> at(i) = image;

        Sprite s;
        s.SetImage(Images->at(i));
        s.SetPosition(X(i) + 300,400);
        s.Resize(200,200);

        wrong_ones->at(i) = s;
    }

        picture.LoadFromFile("resource/img/Wordfill/"+ Word + ".jpg");
        pic.SetImage(picture);
        pic.SetPosition(700,10);
        pic.Resize(300,250);
}


void WordfillGame :: draw(sf::RenderWindow &gameWindow)
{
     for(int i = 0; i < 3; i++){
          gameWindow.Draw( Display -> at(i));
        }

        gameWindow.Draw(pic);

         sf :: String Text;
        string findword = "Complete the word for this \n                picture";

        Text.SetText(findword);
        Text.SetSize(70);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(60,250);
        gameWindow.Draw(Text);

        for(int i = 0; i < 2; i++){
        gameWindow.Draw(wrong_ones -> at(i));
        }

        drawText(gameWindow);
}

void WordfillGame :: drawText(sf::RenderWindow &gameWindow)
{
        sf :: String Text;
        Text.SetText(display);
        Text.SetSize(80);
        Text.SetColor(sf::Color :: Blue);
        Text.SetPosition(200,600);
        gameWindow.Draw(Text);
}
int WordfillGame :: X(int i)
{
 switch(i){
                    case 0:
                                return 10;
                    case 1:
                                return 220;
                    case 2:
                                return 430;

                    default:
                                return NULL;
    }
}

string WordfillGame :: schange(char letter)
{
    string h = "";
    h.append(1,letter);
    return h;
}

string WordfillGame :: random_words()
{
int num = rand() % 15;
switch(num){
    case 0:
             other = 'D';
            return "HAT";
    case 1:
            other = 'T';
            return "CAR";
    case 2:
             other = 'Q';
            return "CAT";
    case 3:
             other = 'W';
            return "CAP";
    case 4:
             other = 'S';
            return "COW";
    case 5:
             other = 'P';
            return "BUG";
    case 6:
             other = 'E';
            return "PIG";
    case 7:
             other = 'K';
            return "HEN";
    case 8:
             other = 'Z';
            return "DOG";
    case 9:
            other = 'V';
            return "SAW";
    case 10:
             other = 'Y';
            return "CAN";
    case 11:
             other = 'T';
            return "PEA";
    case 12:
             other = 'J';
            return "PEN";
    case 13:
             other = 'X';
            return "MAN";
    case 14:
             other = 'B';
            return "SEA";
    case 15:
             other = 'J';
            return "SUN";
     default:
            return NULL;
}
}

vector<char> * WordfillGame :: fill_Word_complete()
{

vector <char> * complete = new vector <char>;

for(int i = 0; i < size; i++){
    complete->push_back(Word.at(i));
    }

int num = rand() % size;
out = complete->at(num);
complete->at(num) = '0';

return complete;
}

vector<char> * WordfillGame :: fill_random_letters()
{
    vector <char> * complete = new vector <char>;
    complete->push_back(out);
    complete->push_back(other);
 
    int num = rand() % 2;
    int num1 = rand() % 2;
    char t = complete->at(num);
    complete->at(num) = complete->at(num1);
    complete->at(num1) = t;

return complete;
}
