#include<iostream>

#include"headers/game.h"

using namespace std;

int main () {
    srand(time(0));
    Game myGame;
    myGame.mainMenu();

    cout << "Thanks for playing! Congratulations, or better luck next time buddy." << endl;

    return 0;
}
