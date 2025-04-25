#include <csignal>
#include<iostream>
#include<fstream>

#include"../headers/game.h"
#include"../headers/spinner.h"
#include"../headers/Board.h"

using namespace std;
/* this is it, the functions where everything happens!

BLUF:

In here, I want to have a function which tracks the location of all players and does the board display function, and
functions to split the text files up into vectors of characters, advisors, riddles, and events.

Variable-wise, I want vectors of players, characters, advisors, riddles, and events.

I then want two functions: gamemasterInit and gamemaster. GMI will do the printing of a character array, some flavor
text, and the "select character" and "select path" menu.

Gamemaster will essentially act as a turn, returning the value of the next player's turn (i.e. if player 1 just played, it'll
return the value for Player 2). In theory, GM should open the player menu, move the player, handle events (both tile and random),
possibly integrate a combat system, then hand it off to the second player.

Finally, I want a endgame function. This displays stats between the two players and tells us who's the winner.
*/

//constructors
Game::Game () {
    /*
    advisorPuller("../input_files/advisors.txt");
    cout << "Advisors good!" << endl;
    characterPuller("../input_files/characters.txt");
    cout << "Characters good!" << endl;
    eventPuller("../input_files/random_events.txt");
    cout << "Events good!" << endl;
    riddlePuller("../input_files/riddles.txt");
    cout << "Riddles good!" << endl;
    */
    cout << "Welcome to..." << endl
    <<
"···································································\n" <<
": _____ _           ___ _        _            __   _    _  __     :\n" <<
":|_   _| |_  ___   / __(_)_ _ __| |___   ___ / _| | |  (_)/ _|___ :\n" <<
":  | | | ' \\/ -_) | (__| | '_/ _| / -_) / _ \\  _| | |__| |  _/ -_):\n" <<
":  |_| |_||_\\___|  \\___|_|_| \\__|_\\___| \\___/_|   |____|_|_| \\___|:\n" <<
"···································································\n" << endl;

    int spin = rand()%2;
    switch (spinner()+(spin-1)) {
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
        cout << "Your mom definitely approves." << endl;
    }
    
    cout << endl;
    //need to figure out what goes in the default constructor
    //player
    //board
    //events
    //advisors
    //characters
    //riddles
}


Game::Game(int playerNumber, string eventsFile, string advisorFile, string characterFile, string riddleFile) {
    //all of these beautiful things, declared!
    return;
}

//Gameplay functions
void Game::gameMasterInit () {
    /*
    advisorPuller("input_files/advisors.txt");
    cout << "Advisors good!" << endl;
    characterPuller("input_files/characters.txt");
    cout << "Characters good!" << endl;
    eventPuller("input_files/random_events.txt");
    cout << "Events good!" << endl;
    riddlePuller("input_files/riddles.txt");
    cout << "Riddles good!" << endl;
    */

    //splash screen
    int spin = rand()%2;
    switch (spinner()+(spin-1)) {
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
        cout << "Your mom definitely approves." << endl;
    }
    
    cout << endl;

    int playerNum = 0, boardSelect=0;
    while (playerNum > 2 || playerNum <= 0) {
        cout << "Enter number of players (1 to 2)" << endl;
        cin >> playerNum;
        if (playerNum != 1 && playerNum != 2) {
            cout << "please double check your maths." << endl;
        }
    }

    while (playerNum != 0) {
        cout << "Player " << playerNum << " , tell me. Do you want to play normal (1) or easy (2)?" << endl;
        cin >> boardSelect;
        Player temp(playerNum-1, 10, 10, 10, 10, 10, boardSelect);
        _players[playerNum-1] = temp;
        playerNum--;
    }

    int players[2][2];

    for (int i = 0; i < playerNum; i++) {
        players[i][0] = 0;
        players[i][1] = _players[i].getBoardType();
    }

    Board gameBoard(players, playerNum);
    gameBoard.initializeBoard();
    gameBoard.displayBoard();

    // this will split all the text files into the vectors used from here on out
    // additionally, it'll display the character array
    // Finally, it will ask players to select a character and a path.
}

void Game::gameMaster () {
    bool gameOver = false;
    int which_turn = 0;
    while (gameOver == false) {
        which_turn = turn(which_turn);
        if (which_turn == -1) {
            gameOver = true;
        }
    }
    // this will be most of the game. The basic logic loop is as follows:
    // Player menu opened
    // Once menu is closed, spinner to move
    // Player movement sent to board
    // Event management - event from tile
        // Might build a combat system later?
    // Event management - random event
        // See above note
    // Checks both player positions to see if they've both reached the end
        // if so, will do a victory function
    // 

    //return player;
}

int Game::turn (int player) {
    Player currentPlayer = _players[player];
    int move_distance = spinner();

    currentPlayer.menu();

    currentPlayer.move(move_distance);
    cout << "Moving " << move_distance << " distance." << endl;

    if (player == 0) {
        return 1;
    } else {
        return 0;
    }
    
    return player;
}

//initialization functions for advisor, character, event, riddle vectors
void Game::advisorPuller(string filename) {
    //this will pull in a file and feed the vector advisors with advisors.
    ifstream file_in(filename);
    
    if (file_in.fail()) {
        cout << "Advisor file doesn't exist." << endl;
        return;
    }

    string current_text = "";
    int idx = 0;
    Advisor currentAdvisor;

    while (getline(file_in, current_text, '|')) {
        if (current_text != "name" && current_text != "ability" && current_text != "description") {
            if (idx == 0) {
                currentAdvisor.name=current_text;
                idx ++;
            } else if (idx == 1) {
                currentAdvisor.ability=current_text;
                idx ++;
            } else if (idx == 2) {
                currentAdvisor.abilityDesc=current_text;
                _advisors.push_back(currentAdvisor);
                idx = 0;
            }
        }
    }
}
void Game::characterPuller(string filename) {
    //this will pull in a file and feed the vector characters with characters from the file
    ifstream file_in(filename);
    
    if (file_in.fail()) {
        cout << "Character file doesn't exist." << endl;
        return;
    }

    string current_text = "";
    int current_num = 0; //using stod(string var) has caused me issues in the past, so I'm going to use a intermediate int to try and sidestep that.
    int idx = 0; //I use IDX to essentially track where I am in the text file. This is slightly easier than doing some kind of reference thing,
                 // where I store the first line and then compare current input to current. Probably could replace first if with a .ignore if I did
                 // stringstream, I'll do that later, if I have time.
    Characters currentCharacter;

    while (getline(file_in, current_text, '|')) {
        //if (current_text != "playerName" age|strength|stamina|wisdom|pridePoints) {
            if (idx == 0) {
                currentCharacter.name=current_text;
                idx ++;
            } else if (idx == 1) {
                current_num=stod(current_text);
                currentCharacter.age=current_num;
                idx ++;
            } else if (idx == 2) {
                current_num=stod(current_text);
                currentCharacter.strength=current_num;
                idx ++;
            } else if (idx == 3) {
                current_num=stod(current_text);
                currentCharacter.stamina=current_num;
                idx++;
            } else if (idx ==4) {
                current_num=stod(current_text);
                currentCharacter.wisdom=current_num;
                idx++;
            } else if (idx == 5) {
                current_num=stod(current_text);
                currentCharacter.points=current_num;
                _characters.push_back(currentCharacter);
                idx = 0;
            }
        //}
    }
}
void Game::eventPuller(string filename) {
    //this will pull in a file and feed the vector events with events from the file
    ifstream file_in(filename);
    
    if (file_in.fail()) {
        cout << "Events file doesn't exist." << endl;
        return;
    }

    string current_text = "";
    int current_num = 0; //using stod(string var) has caused me issues in the past, so I'm going to use a intermediate int to try and sidestep that.
    int idx = 0; //I use IDX to essentially track where I am in the text file. This is slightly easier than doing some kind of reference thing,
                 // where I store the first line and then compare current input to current. Probably could replace first if with a .ignore if I did
                 // stringstream, I'll do that later, if I have time.
    Events currentEvent;

    while (getline(file_in, current_text, '|')) {
        //if (current_text != "playerName" age|strength|stamina|wisdom|pridePoints) {
            if (idx == 0) {
                currentEvent.event=current_text;
                idx ++;
            } else if (idx == 1) {
                current_num=stod(current_text);
                currentEvent.path=current_num;
                idx ++;
            } else if (idx == 2) {
                current_num=stod(current_text);
                currentEvent.advisor=current_num;
                idx ++;
            } else if (idx == 3) {
                current_num=stod(current_text);
                currentEvent.points=current_num;
                _events.push_back(currentEvent);
                idx = 0;
            }
        //}
    }
}
void Game::riddlePuller(string filename){
    //this will open the riddles file and fill vector with riddles
    ifstream file_in(filename);
    
    if (file_in.fail()) {
        cout << "Riddle file doesn't exist." << endl;
        return;
    }

    string current_text = "";
    int idx = 0; //I use IDX to essentially track where I am in the text file. This is slightly easier than doing some kind of
    // reference thing, where I store the first line and then compare current input to current. Probably could replace first if
    // with a .ignore if I did stringstream, I'll do that later, if I have time.
    Riddles currentRiddle;

    while (getline(file_in, current_text, '|')) {
        //if (current_text != "playerName" age|strength|stamina|wisdom|pridePoints) {
            if (idx == 0) {
                currentRiddle.riddle=current_text;
                idx ++;
            } else if (idx == 1) {
                currentRiddle.type=current_text;
                idx ++;
            } else if (idx == 2) {
                currentRiddle.answer=current_text;
                _riddles.push_back(currentRiddle);
                idx = 0;
            }
        //}
    }
}

//menu functions, selectors, similar
void Game::characterSelect() {
    //menu that'll get called at the start for choosing characters from the vector.
}
void Game::advisorSelect() {
    //menu that'll get called for choosing advisors, whenever that tile gets hit.
}
void Game::mainMenu() {
    int userIn = 0;
    string filename = "../saved/",input;
    while (userIn != 4) {
        cout << "Menu options (select by number):" << endl
             << "1. New Game" << endl
             << "2. Load Game" << endl
             << "3. High Score" << endl
             << "4. Exit Game" << endl;
        cin >> userIn;

        switch (userIn) {
            case 1:
            gameMasterInit();
            break;
            case 2:
            cout << "Enter saved game name:" << endl;
            cin >> input;
            filename += input;
            filename += ".save";
            loadGame(filename);
            break;
            case 3:
            highScore();
            break;
            case 4:
            cout << "Thanks for playing!" << endl;
            default:
            cout << "Invalid input, try again!";
            break;
        }
    }
}
void Game::gameOver() {
    cout << "Congrats on reaching the end of the game!" << endl;
    //for (int i = 0; i < _players.size(); i++) {
    //    cout << "Player " << i << "'s score is: " << _players.at(i).getPoints() << endl;
    //}

    cout << "Thank you for playing! Taking you back to the main menu..." << endl;
}

void Game::highScore() {

}

//the magic I will work on later!
void Game::saveGame() {
    //this, when called, will print current game state to a text file
}
void Game::loadGame(string savedGame) {
    //this will take a given savegame, add .txt to it, find it, and load it.
    string filename = "";
    cout << "Tell me the name of your save file." << endl;
    cin >> filename;
}
void Game::combat(int player, int scenario) {

}