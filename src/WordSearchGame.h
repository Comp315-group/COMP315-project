#ifndef WORDSEARCHGAME_H
#define WORDSEARCHGAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <string>

#endif //  WORDSEARCHGAME_H

using namespace std;
using namespace sf;

class WordSearchGame{

    public:
        //default constructor
        WordSearchGame();

        //draws the memory game grid and its components to a specified window
        void draw(RenderWindow &gameWindow);

        //draws text to a specified window
        void drawText(RenderWindow &gameWindow);

        //returns if the memory game has been solved
        bool gameOver();


        void correct(int,int);

        //updates the location of where the mouse was clicked on a specified window
        void update(int xpos, int ypos);

    private:
        //generates the columns and rows of the word search grid
        vector < vector <string> * > * generateGrid(int value);

        //returns a x co-ordinate based on its input
        int X(int i);

        //returns a y co-ordinate based on its input
        int Y(int i);

        //records x position of the mouse click
        int xPos;

        //records y position of the mouse click
        int yPos;

        //records if two tiles have the same image
        size_t found;

        //stores the the list of image sprites
        vector<Sprite> * SpriteImages;

        //stores the the list of image Images
        vector<Image> * Images;

        //records if the memory game has been solved
        bool wordsearchGameOver;

        //stores the columns and rows of the word search grid
        vector < vector <string> * > * grid;

        //stores the word that must be found
        string word;

        //stores what letter of the word have been found
        string displayWord;
};

/*
    default constructor
*/
WordSearchGame::WordSearchGame(){
    //starts a new game as being unsolved
    wordsearchGameOver = false;

    //randomly generates a new grid
    grid = generateGrid((rand()%7)+1);

    //initializes the vectors associated with the Image and Sprite storage
    SpriteImages = new vector<Sprite> (9);
    Images = new vector<Image> (9);

    //stores the number of tiles added to the grid
    int count = 0;

    Image image;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){

                //loads the image from the resource folder
                image.LoadFromFile("resource/img/WordSearch/" + (grid->at(i))->at(j) + ".png");

                //stores the image in its appropriate vector
                Images->at(count) = image;

                /*
                sets the  and y co-ordinates of the image, resizes it
                and stores it in its appropriate vector
                */
                Sprite s;
                s.SetImage(Images->at(count));
                s.SetPosition(X(i),Y(j));
                s.Resize(75,75);
                SpriteImages->at(count) = s;
                count++;
            }
        }

    displayWord = "";
}


/*
    returns the x co-ordinate of where the mouse was clicked
*/
int WordSearchGame::X(int i){
    switch(i){
        case 0:
            return 400;
        case 1:
            return 475;
        case 2:
            return 550;
        case 3:
            return 625;
        default:
            return NULL;
    }
}

/*
    returns the y co-ordinate of where the mouse was clicked
*/
int WordSearchGame::Y(int j){
    switch(j){
        case 0:
            return 300;
        case 1:
            return 375;
        case 2:
            return 450;
        case 3:
            return 525;
        default:
            return NULL;
    }
}

/*
    determines the result of a mouse click
*/
void WordSearchGame::update(int xpos, int ypos){

    /*
        Each check determines where the mouse has been clicked. If the mouse click
        occured within a valid tile range there is a check to determine if the tile
        clicked contains a letter which forms the next part of the word. If it is
        then the displayed word is appended with the newly clicked letter.
    */
    if(xpos>=400&&xpos<=475){
        if(ypos>=300&&ypos<=375){
            found = word.find(displayWord+(grid->at(0))->at(0));
            if(int(found)==0)
            displayWord+=(grid->at(0))->at(0);
        }
        else if(ypos>=375&&ypos<=450){
            found = word.find(displayWord+(grid->at(0))->at(1));
            if(int(found)==0)
            displayWord+=(grid->at(0))->at(1);
        }
        else if(ypos>=450&&ypos<=525){
            found = word.find(displayWord+(grid->at(0))->at(2));
            if(int(found)==0)
            displayWord+=(grid->at(0))->at(2);
        }
    }

    else if(xpos>=475&&xpos<=550){
        if(ypos>=300&&ypos<=375){
            found = word.find(displayWord+(grid->at(1))->at(0));
            if(int(found)==0)
            displayWord+=(grid->at(1))->at(0);
        }
        else if(ypos>=375&&ypos<=450){
            found = word.find(displayWord+(grid->at(1))->at(1));
            if(int(found)==0)
            displayWord+=(grid->at(1))->at(1);
        }
        else if(ypos>=450&&ypos<=525){
            found = word.find(displayWord+(grid->at(1))->at(2));
            if(int(found)==0)
            displayWord+=(grid->at(1))->at(2);
        }
    }

    else if(xpos>=550&&xpos<=625){
        if(ypos>=300&&ypos<=375){
            found = word.find(displayWord+(grid->at(2))->at(0));
            if(int(found)==0)
            displayWord+=(grid->at(2))->at(0);
        }
        else if(ypos>=375&&ypos<=450){
            found = word.find(displayWord+(grid->at(2))->at(1));
            if(int(found)==0)
            displayWord+=(grid->at(2))->at(1);
        }
        else if(ypos>=450&&ypos<=525){
            found = word.find(displayWord+(grid->at(2))->at(2));
            if(int(found)==0)
            displayWord+=(grid->at(2))->at(2);
        }
    }

    //checks to see if the player has found the word
    if(displayWord.compare(word)==0)
        wordsearchGameOver = true;
}

/*
    draws the memory game grid to the specified window
*/
void WordSearchGame::draw(sf::RenderWindow &gameWindow)
{
        int count = 0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                gameWindow.Draw(SpriteImages -> at(count));
                count++;
            }
        }

        sf :: String Text;
        string findword = " Find the word " + word;

        Text.SetText(findword);
        Text.SetSize(85);
        Text.SetColor(sf::Color :: Red);
        Text.SetPosition(10,50);
        gameWindow.Draw(Text);

        drawText(gameWindow);
}

/*
    draws text to the specified window
*/
void WordSearchGame::drawText(sf::RenderWindow &gameWindow)
{
    sf::String Text;
        Text.SetText(displayWord);
        Text.SetSize(90);
        Text.SetColor(sf::Color :: Blue);
        Text.SetPosition(150,550);
        gameWindow.Draw(Text);
}

/*
    returns if the game has been completed
*/
bool WordSearchGame::gameOver(){
    return wordsearchGameOver;
}

/*
    generates a word search game grid determined on the integer input
*/
vector < vector <string> * > * WordSearchGame::generateGrid(int value){
    vector < vector <string> * > * temp = new vector < vector <string> * >;
    vector <string> * colA = new vector <string>;
    vector <string> * colB = new vector <string>;
    vector <string> * colC = new vector <string>;

    switch(value){
        case 1:{
            colA->push_back("A");
            colA->push_back("C");
            colA->push_back("F");

            colB->push_back("G");
            colB->push_back("A");
            colB->push_back("Q");

            colC->push_back("D");
            colC->push_back("T");
            colC->push_back("L");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "CAT";
            return temp;
        }

        case 2:{
            colA->push_back("B");
            colA->push_back("X");
            colA->push_back("Z");

            colB->push_back("L");
            colB->push_back("A");
            colB->push_back("B");

            colC->push_back("A");
            colC->push_back("S");
            colC->push_back("G");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "BAG";
            return temp;
        }

        case 3:{
            colA->push_back("G");
            colA->push_back("D");
            colA->push_back("I");

            colB->push_back("O");
            colB->push_back("A");
            colB->push_back("L");

            colC->push_back("D");
            colC->push_back("G");
            colC->push_back("U");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "DOG";
            return temp;
        }

        case 4:{
            colA->push_back("D");
            colA->push_back("E");
            colA->push_back("G");

            colB->push_back("H");
            colB->push_back("O");
            colB->push_back("Y");

            colC->push_back("C");
            colC->push_back("O");
            colC->push_back("C");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "COD";
            return temp;
        }

        case 5:{
            colA->push_back("F");
            colA->push_back("E");
            colA->push_back("C");

            colB->push_back("G");
            colB->push_back("A");
            colB->push_back("A");

            colC->push_back("H");
            colC->push_back("K");
            colC->push_back("R");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "CAR";
            return temp;
        }

        case 6:{
            colA->push_back("M");
            colA->push_back("L");
            colA->push_back("A");

            colB->push_back("S");
            colB->push_back("I");
            colB->push_back("U");

            colC->push_back("R");
            colC->push_back("O");
            colC->push_back("P");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "AIR";
            return temp;
        }

        case 7:{
            colA->push_back("S");
            colA->push_back("W");
            colA->push_back("F");

            colB->push_back("Z");
            colB->push_back("K");
            colB->push_back("L");

            colC->push_back("H");
            colC->push_back("P");
            colC->push_back("Y");

            temp->push_back(colA);
            temp->push_back(colB);
            temp->push_back(colC);

            word = "FLY";
            return temp;
        }


        default:
            return NULL;
    }
}
