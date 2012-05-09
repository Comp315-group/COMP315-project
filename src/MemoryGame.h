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
        //default constructor
        MemoryGame();

        //returns if the memory game has been solved
        bool gameOver();

        //draws the memory game grid and its components to a specified window
        void draw(RenderWindow &gameWindow);

        //updates the location of where the mouse was clicked on a specified window
        void update(int xpos, int ypos, RenderWindow &gameWindow);

    private:
        //generates a memory game grid determined by the input value
        vector <string> * generateGrid(int value);

        //randomizes the tile images of the grid
        void randomize();

        //returns a x co-ordinate based on its input
        int X(int i);

        //returns a y co-ordinate based on its input
        int Y(int i);

        //records x position of the mouse click
        int xPos;

        //records y position of the mouse click
        int yPos;

        //records the location of first clicked tile
        int revealA;

        //records the location of second clicked tile
        int revealB;

        //records the number of tiles still hidden
        int hiddenTiles;

        //records how many tiles are revealed
        int noRevealed;

        //records if the game has been completed
        bool memoryGameOver;

        //records if two tiles have the same image
        size_t found;

        //stores the grid of image names
        vector <string> * grid;

        //stores the the list of image sprites
        vector<Sprite> * SpriteImages;

        //stores the list of image back sprites
        vector<Sprite> * SpriteBacks;

        //stores the list of matched image sprites
        vector<Sprite> * SpriteBlanks;

        //stores the the list of image Images
        vector<Image> * Images;

        //stores the list of image back Images
        vector<Image> * Backs;

        //stores the list of matched image Images
        vector<Image> * Blanks;
};

/*
    default constructor
*/
MemoryGame::MemoryGame(){
    //starts a new game as being unsolved
    memoryGameOver = false;

    //sets the number of revealed tiles to 0
    noRevealed = 0;

    //sets the first revealed tile to a value out of range
    revealA = -1;

    //sets the second revealed tile to a value out of range
    revealB = -1;

    //sets the number of unrevealed tiles to 16
    hiddenTiles = 16;

    //randomly generates a new grid
    grid = generateGrid((rand()% 3)+1);

    //randomizes the contents of the grid
    randomize();


    //initializes the vectors associated with the Image and Sprite storage
    SpriteImages = new vector<Sprite> (16);
    SpriteBacks = new vector<Sprite> (16);
    SpriteBlanks = new vector<Sprite> (16);

    Images = new vector<Image> (16);
    Backs = new vector<Image> (16);
    Blanks = new vector<Image> (16);

    //creates a new Image to store the front image of the tile
    Image image;

    //creates aand loads a new Image to store the back image of the tile
    Image back;
    back.LoadFromFile("resource/img/memory/back.png");

    //creates aand loads a new Image to store a revealed tile
    Image blank;
    blank.LoadFromFile("resource/img/memory/blank.png");

    //stores the number of tiles added to the grid
    int count = 0;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            //loads the tile image from the resource folder
            image.LoadFromFile("resource/img/memory/" + grid->at(count) + ".png");

            //stores the image in its appropriate vector
            Images->at(count) = image;

            //stores the image in its appropriate vector
            Backs->at(count) = back;

            //stores the image in its appropriate vector
            Blanks->at(count) = blank;

            /*
                sets the  and y co-ordinates of the tile image, resizes it
                and stores it in its appropriate vector
            */            Sprite s;
            s.SetImage(Images->at(count));
            s.SetPosition(X(i),Y(j));
            s.Resize(75,75);
            SpriteImages->at(count) = s;

            /*
                sets the  and y co-ordinates of the tile back, resizes it
                and stores it in its appropriate vector
            */
            Sprite covered;
            covered.SetImage(Backs->at(count));
            covered.SetPosition(X(i),Y(j));
            covered.Resize(75,75);
            SpriteBacks->at(count) = covered;


            /*
                sets the  and y co-ordinates of the blank tile, resizes it
                and stores it in its appropriate vector
            */
            Sprite blank_;
            blank_.SetImage(Blanks->at(count));
            blank_.SetPosition(X(i),Y(j));
            blank_.Resize(75,75);
            SpriteBlanks->at(count) = blank_;

            //increments the number of stored tiles
            count++;
        }
    }
}

/*
    returns if the game has been completed
*/
bool MemoryGame::gameOver(){
    return memoryGameOver;
}

/*
    returns the x co-ordinate of where the mouse was clicked
*/
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

/*
    returns the y co-ordinate of where the mouse was clicked
*/
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

/*
    determines the result of a mouse click
*/
void MemoryGame::update(int xpos, int ypos, RenderWindow &gameWindow){

    /*
        Each check determines where the mouse has been clicked. If the mouse click
        occured within a valid tile range there is a check to determine if the tile
        has already been removed. If the tile is still present and is not currently
        revealed then either revealA or revealB is set to the location of the clicked
        tile
    */
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

    //draws the game window
    draw(gameWindow);

    //checks to see if two tiles have been revealed
    if(noRevealed==2){
        //check to see if both revelead tiles are of the same image
        found = (grid->at(revealA)).find(grid->at(revealB));
        if((int)found==0){
            //sets both tiles to revealed they are of the same image
            grid->at(revealA) = "";
            grid->at(revealB) = "";
            //decrements the number of non-revealed tiles
            hiddenTiles = hiddenTiles -2;
        }

        //resets flipped tile positions
        revealA = -1;
        revealB = -1;
        noRevealed = 0;
    }

    //checks if there are any remaining tiles left covered
    if(hiddenTiles==0)
       memoryGameOver = true;
}

/*
    draws the memory game grid to the specified window
*/
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

/*
    generates a memory game grid determined on the integer input
*/
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

/*
    randomizes the image grid to ensure no two games are the same
*/

void MemoryGame::randomize(){

    //randomly swaps the image locations around 50 times
    for(int i=0;i<50;i++){
        string temp;
        int a = rand()%16;
        int b = rand()%16;

        //swaps two images around in the vector
        temp = grid->at(a);
        grid->at(a) = grid->at(b);
        grid->at(b) = temp;
    }
}
