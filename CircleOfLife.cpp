//header files:
#include"headers/libraries.h"
#include"headers/players.h"
#include"headers/Board.h"
#include <curses.h>
#include<stdlib.h>

//initial stuff
int main () {
    srand(time(0));
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