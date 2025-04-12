//header files:
#include"headers/libraries.h"
//#include"headers/helpers.h"
#include"headers/player.h"
#include"headers/game.h"
#include"headers/Board.h"

int spinner () {
    int result = rand()%6;
    return result+1;
}

//initial stuff
int main () {
    srand(time(0));

    cout << "Welcome to..." << endl
    <<
"···································································\n" <<
": _____ _           ___ _        _            __   _    _  __     :\n" <<
":|_   _| |_  ___   / __(_)_ _ __| |___   ___ / _| | |  (_)/ _|___ :\n" <<
":  | | | ' \\/ -_) | (__| | '_/ _| / -_) / _ \\  _| | |__| |  _/ -_):\n" <<
":  |_| |_||_\\___|  \\___|_|_| \\__|_\\___| \\___/_|   |____|_|_| \\___|:\n" <<
"···································································\n" << endl;

    switch (spinner()) {
        case 0:
        cout << "which is definitely legally distinct from The Lion King." << endl;
        break;
        case 1:
        cout << "AAAAAAAAAAAAAAAAAAAAAAAAH SAVENYA BAGANICHI ALA" << endl;
        break;
        case 2:
        cout << "I'm surrounded by idiots." << endl;
        break;
        case 3:
        cout << "\"What\'s a motto?\" \"Nothing. What\'s a motto with you?\"" << endl;
        break;
        case 4:
        cout << "Hakkuna Matata!" << endl;
        break;
        case 5:
        cout << "Slimy... Yet Satisfying." << endl;
        break;
        default:
        cout << "which is definitely legally distinct from The Lion King." << endl;
    }
    
    cout << endl;

    Board gameBoard(2);
    gameBoard.initializeBoard(0, 1);
    gameBoard.displayBoard();

    // we're going to interact essentially entirey through 
    return 0;
}