#include<iostream>
#include"headers/game.h"

using namespace std;
//I wish the other files were this clean...

int main () {
    //seed random (which spinner is capable of anyway, so idk why I'm doing this)
    srand(time(0));
    //initalize the game, that's all this needs to do!
    Game myGame;
    myGame.mainMenu();
    //somewhat pointless "goodbye" statement - lets me know program is closing.
    cout << "Thanks for playing! Come back sometime." << endl;

    return 0;
}