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

                string random_words();
                vector<char> * fill_Word_complete();
                vector<char> * fill_random_letters();
                char to_fill();

                bool WordfillGameOver;
                void set_correctString(int);
                int X(int i);
                 string schange(char);



};

WordfillGame::WordfillGame()
{
    Word = random_words();
    size = Word.length();
    Word_complete = fill_Word_complete();
    random_letters = fill_random_letters();
    WordfillGameOver = false;
    display = "";
}

bool WordfillGame :: gameOver()
{
return WordfillGameOver;
}

void WordfillGame :: correct(int x, int y)
{

    if((x >= 320&& x <=510) && (y >=400 && y <= 600)){
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

void WordfillGame :: draw(sf::RenderWindow &gameWindow)
{
    vector<Sprite> *Test = new vector<Sprite>(3);
    Image image;

        for(int i = 0; i < 3; i++){
        image.LoadFromFile("resource/img/Wordfill/"  + schange(Word_complete->at(i)) + ".png");

        Sprite s;
        s.SetImage(image);
        s.SetPosition(X(i),50);
        s.Resize(200,200);

        Test->at(i) = s;

        gameWindow.Draw(Test -> at(i));
        }

        Sprite t;
        image.LoadFromFile("resource/img/Wordfill/"+ Word + ".jpg");
        t.SetImage(image);
        t.SetPosition(700,10);
        t.Resize(300,250);
        gameWindow.Draw(t);

         sf :: String Text;
        string findword = " Complete the word for this picture \n      by clicking on the letters below";

        Text.SetText(findword);
        Text.SetSize(60);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(40,250);
        gameWindow.Draw(Text);

        for(int i = 0; i < 2; i++){
        image.LoadFromFile("resource/img/Wordfill/"  + schange(random_letters->at(i)) + ".png");

        Sprite s;
        s.SetImage(image);
        s.SetPosition(X(i) + 300,400);
        s.Resize(200,200);

        Test->at(i) = s;

        gameWindow.Draw(Test -> at(i));

        drawText(gameWindow);
        }
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
int num = rand() % 4;
switch(num){
    case 0:
            return "HAT";
    case 1:
            return "CAR";
    case 2:
            return "CAT";
    case 3:
            return "CAP";
    case 4:
            return "COW";
    case 5:
            return "BUG";
    case 6:
            return "PIG";
    case 7:
            return "HEN";
    case 8:
            return "DOG";
    case 9:
            return "SAW";
    case 10:
            return "CAN";
    case 11:
            return "PEA";
    case 12:
            return "PEN";
    case 13:
            return "MAN";
    case 14:
            return "SEA";
    case 15:
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
    int n = rand() % 26;
    char c = (n+65);
    complete->push_back(c);

return complete;
}
