//header files:
#include"headers/libraries.h"
#include"headers/players.h"
#include"headers/Board.h"
#include <curses.h>
#include<stdlib.h>

int spinner () {
    int result = rand()%6;

    return result+1;
}

//initial stuff
int main () {
    srand(time(0));

    cout << "Welcome to the" << endl
    <<
"···································································\n" <<
": _____ _           ___ _        _            __   _    _  __     :\n" <<
":|_   _| |_  ___   / __(_)_ _ __| |___   ___ / _| | |  (_)/ _|___ :\n" <<
":  | | | ' \\/ -_) | (__| | '_/ _| / -_) / _ \\  _| | |__| |  _/ -_):\n" <<
":  |_| |_||_\\___|  \\___|_|_| \\__|_\\___| \\___/_|   |____|_|_| \\___|:\n" <<
"···································································\n";

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
    

    Board gameBoard(2);
    gameBoard.initializeBoard(0, 1);
    gameBoard.displayBoard();

    /*
    gameBoard.movePlayer(0);
    gameBoard.getPlayerPosition(0);
    gameBoard.displayBoard();
    cout << endl << "+++++++++++++++++" << endl << endl << "new board:" << endl;

    gameBoard.movePlayer(1);
    gameBoard.getPlayerPosition(1);
    gameBoard.displayBoard();
    cout << endl << "+++++++++++++++++" << endl << endl << "new board:" << endl;

    
    for (int i = 0; i < 10; i++) {
        gameBoard.movePlayer(1);
        gameBoard.getPlayerPosition(1);
        
        gameBoard.displayBoard();
        cout << endl << "+++++++++++++++++" << endl << endl << "new board:" << endl;

        if (i%2 == 0) {
            for (int j = 0; j < 3; j++) {
                gameBoard.movePlayer(0);
            }
        }
    }
    gameBoard.movePlayer(1);
    gameBoard.getPlayerPosition(1);
    gameBoard.displayBoard();
    cout << endl << "+++++++++++++++++" << endl;
    */
    return 0;
}