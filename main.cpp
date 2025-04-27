#include <algorithm>
#include<iostream>

//header files:
//#include"headers/libraries.h" //this is actively being used. IDK what VS Code is on about.
//#include"headers/helpers.h"
//#include"headers/player.h"
//#include "headers/Board.h"
#include"headers/game.h"
#include"headers/Board.h"

using namespace std;

//these headers will eventually be used, I promise!

//int spinner();

//initial stuff
int main () {
    srand(time(0));

    int players[2][2];
    players[0][0] = 0;
    players[0][1] = 0;
    players[1][0] = 0;
    players[1][1] = 0;
    

    Board gameBoard(players, 2);
    //gameBoard.initializeBoard(0);
    gameBoard.displayBoard();
    gameBoard.movePlayer(0,4);
    gameBoard.displayBoard();
    gameBoard.movePlayer(1, 5);
    gameBoard.displayBoard();

    //going to retheme, considering sci-fi or western theme...

/* TEST STUFF

    //Game theGame;

    //theGame.gameMasterInit();

    //Game myGame(2, "help.txt", "help.txt", "help.txt", "help.txt");

    //Game myGame;

    //myGame.gameMasterInit();

    // we're going to interact essentially entirey through gamemaster functions, I'll need to make those return player turns
    // gamemaster init
    // for loop until gamemaster returns a non-player number (-1)
        // int playerTurn = 0;
        // playerTurn = game.gamemaster(playerTurn); - I think something like this? Need to make sure it flips btwn players
        // 
    // game.ending, then credits
*/

    //TEST BOARD:
    /*
    int player_arr[2][2];

    for (int i = 0; i < 2; i++) {
        cout << "Player " << i << endl;
        for (int j = 0; j < 2; j++) {
            player_arr[i][j] = 0;
            cout << player_arr[i][j] << " ";
        }
        cout << endl;
    }

    Board myBoard(player_arr, 2);
    myBoard.initializeBoard();
    myBoard.displayBoard();

    myBoard.movePlayer(0, 10);
    myBoard.displayBoard();
    myBoard.movePlayer(1,3);
    myBoard.displayBoard();
    */


    cout << "Thanks for playing! Congratulations, or better luck next time buddy." << endl;

    return 0;
}
