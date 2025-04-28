#include<csignal>
#include<iostream>
#include<fstream>
#include<ostream>
#include<sstream>
#include<string>
#include<chrono>

#include"../headers/game.h"
#include"../headers/spinner.h"
#include"../headers/Board.h"
#include"../headers/score.h"

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
    //loading variables...
    cout << "Initializing new game..." << endl;
    advisorPuller("input_files/advisors.txt");
    characterPuller("input_files/characters.txt");
    eventPuller("input_files/random_events.txt");
    riddlePuller("input_files/riddles.txt");

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

    mainMenu();
}

//Gameplay functions
void Game::gameMasterInit () {
    cout << endl;

    int playerNum = 0, boardSelect=0;
    while (playerNum > 2 || playerNum <= 0) {
        cout << "Enter number of players (1 to 2)" << endl;
        cin >> playerNum;
        if (playerNum != 1 && playerNum != 2) {
            cout << "please double check your maths." << endl;
        }
    }

    for (int i = 0; i < playerNum; i++) {
        cout << "Player " << i+1 << "... let's intialize." << endl;
        cout << "First, tell me. Do you want to play normal (1) or easy (2)?" << endl;
        cin >> boardSelect;
        
        boardSelect--;

        Characters temp_char = characterSelect();

        Player temp(i, temp_char.age, temp_char.stamina, temp_char.strength, temp_char.wisdom,temp_char.points, boardSelect);

        if (boardSelect == 1) {
            cout << "Since you have selected the easier difficulty, please select an advisor." << endl;
            Advisor temp_advise = advisorSelect();
            temp.setAdvisor(temp_advise);
            temp.changeStamina(500);
            temp.changeStamina(500);
            temp.changeWisdom(1000);
        } else {
            temp.changePoints(5000);
            temp.changeStamina(200);
            temp.changeStamina(200);
            temp.changeWisdom(200);
        }
        _players.push_back(temp);
    }

    int players[2][2];

    for (int i = 0; i < 2; i++) {
        players[i][0] = 0;
        players[i][1] = _players[i].getBoardType();
    }

    Board gameBoard(players, playerNum);
    _theBoard = gameBoard;
    _theBoard.initializeBoard();
    _theBoard.displayBoard();

    gameMaster();
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
    int numPlayers = _players.size();
    char tileType;
    int userIn;

    if (currentPlayer.getLocation() >= 51) {
        if (numPlayers <= 1) {
            gameOver();
        } else if (player == 0) {
            return 1;
        } else {
            return 0;
        } 
    } else if (_players[0].getLocation() >= 51 && _players[1].getLocation() >= 51) {
        //check if both players have won
        gameOver();
    } else {

        currentPlayer.menu();

        //Tile type chars are: O (last block), Y (first block), G (grasslands), P (advisor), U (challenge), R (graveyard), N (hyena), B (oasis)
        tileType = _theBoard.movePlayer(player, move_distance);
        cout << "Tile type is " << tileType << endl;
        currentPlayer.move(move_distance);
        cout << "Moving " << move_distance << " distance." << endl;

        _theBoard.displayBoard();

        cout << "Landed on a ";
        if (tileType == 'O') {
            cout << "victory tile! Congrats!" << endl;
            if (player == 0) {
                return 1;
            } else {
                return 0;
            }
        } else if (tileType == 'G') {
            cout << "grasslands tile. ";
            if (spinner()%2 == 0) {
                event(player);
            } else {
                cout << "You may rest this turn." << endl;
            }
        } else if (tileType == 'P') {
            cout << "advisior tile. You feel greatly rested, and suddently quite wise." << endl;;
            userIn = 0;

            currentPlayer.changeWisdom(300);
            currentPlayer.changeStamina(300);
            currentPlayer.changeStrength(300);

            while (userIn < 1 && userIn > 2) {
                cout << "Do you wish to pick a new advisor? 1 for yes, 2 for no, 3 to see current advisor" << endl;
                cin >> userIn;
                if (userIn == 1) {
                    currentPlayer.setAdvisor(advisorSelect());
                    break;
                } else if (userIn == 2) {
                    break;                
                } else {
                    Advisor playerAdvisor = currentPlayer.getPlayerAdvisor();
                    cout << "Advisor: " << playerAdvisor.name << " Ability: " << playerAdvisor.ability << endl << "Ability Description" << playerAdvisor.abilityDesc << endl;
                }
            }
        } else if (tileType == 'U') {
            riddleEncounter(player);
        } else if (tileType == 'R') {
            cout << "a graveyard tile. The sights, the smells, are terrible. You faint and wake up 10 tiles back." << endl;
            currentPlayer.move(-10);
            //This forces the player to move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points.
            currentPlayer.changeWisdom(-100);
            currentPlayer.changeStamina(-100);
            currentPlayer.changeStrength(-100);
        } else if (tileType == 'N') {
            //The Hyenas are on the prowl! They drag you back to where you were last, and the journey comes at a cost.
            // This returns the player to their previous position. In addition, the player’s Stamina Points decrease by 300 Points.
            combat(player, 1);
        } else if (tileType == 'B') {
            cout << "an oasis. You feel quite rested." << endl;
            //200 Stamina, Strength, and Wisdom Points.
            currentPlayer.changeStamina(200);
            currentPlayer.changeStrength(200);
            currentPlayer.changeWisdom(100);
        }
    }

    cout << "Player " << player+1 << "'s turn is over." << endl;
    if (player == 0 && numPlayers > 1) {
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
    //check to see if file works
    if (file_in.fail()) {
        cout << "Advisor file doesn't exist." << endl;
        return; //false;
    } else {
        cout << "Advisor file loading... ";
    }

    string currentText = "", currentLine = "";
    getline (file_in, currentLine);

    while (getline(file_in, currentLine)) {
        stringstream linestream (currentLine);
        int idx = 0;

        Advisor currentAdvisor;

        while (getline(linestream, currentText, '|')) {
            if (idx == 0) {
                currentAdvisor.name=currentText;
                idx ++;
            } else if (idx == 1) {
                currentAdvisor.ability=currentText;
                idx ++;
            } else if (idx == 2) {
                currentAdvisor.abilityDesc=currentText;
                _advisors.push_back(currentAdvisor);
                idx = 0;
            }
        }
    }
    cout << "file loaded!" << endl;
}
void Game::characterPuller(string filename) {
    //this will pull in a file and feed the vector characters with characters from the file
    ifstream file_in(filename);
    
    if (file_in.fail()) {
        cout << "Character file doesn't exist." << endl;
        return;
    } else {
        cout << "Character file loading... ";
    }

    string currentText = "", currentLine = "";
    double currentNum = 0;
    getline (file_in, currentLine);

    while (getline(file_in, currentLine)) {
        stringstream linestream (currentLine);
        int idx = 0;

        Characters currentCharacter;

        while (getline(linestream, currentText, '|')) {
            if (idx == 0) {
                currentCharacter.name=currentText;
                idx ++;
            } else if (idx == 1) {
                currentNum=stod(currentText);
                currentCharacter.age=currentNum;
                idx ++;
            } else if (idx == 2) {
                currentNum=stod(currentText);
                currentCharacter.strength=currentNum;
                idx ++;
            } else if (idx == 3) {
                currentNum=stod(currentText);
                currentCharacter.stamina=currentNum;
                idx++;
            } else if (idx ==4) {
                currentNum=stod(currentText);
                currentCharacter.wisdom=currentNum;
                idx++;
            } else if (idx == 5) {
                currentNum=stod(currentText);
                currentCharacter.points=currentNum;
                _characters.push_back(currentCharacter);
                idx = 0;
            }
        }
    }
    cout << "file loaded!" << endl;
}
//broken, need more complicated logic!
void Game::eventPuller(string filename) {
    //this will pull in a file and feed the vector events with events from the file
    ifstream file_in(filename);
    bool easy = false;
    
    if (file_in.fail()) {
        cout << "Events file doesn't exist." << endl;
        return;
    } else {
        cout << "Event file loading... ";
    }

    string currentText = "", currentLine = "";
    int current_num = 0;

    getline (file_in, currentLine); //skip the first line

    while (getline(file_in, currentLine)) {

        stringstream linestream (currentLine);
        int idx = 0;

        Events currentEvent;

        while (getline(linestream, currentText, '|')) {
            if (idx == 0) {
                currentEvent.event=currentText;
                idx ++;
            } else if (idx == 1) {
                current_num=stoi(currentText);
                if (current_num == 0) {
                    easy = true;
                } else {
                    easy = false;
                }
                currentEvent.path=current_num;
                idx ++;
            } else if (idx == 2) {
                current_num=stoi(currentText);
                currentEvent.advisor=current_num;
                idx ++;
            } else if (idx == 3) {
                current_num=stoi(currentText);
                currentEvent.points=current_num;
                if (easy) {
                    _easy_events.push_back(currentEvent);
                } else {
                    _norm_events.push_back(currentEvent);
                }
                idx = 0;
            } 
        }
    }

    cout << "file loaded!" << endl;
}
void Game::riddlePuller(string filename) {
    //this will open the riddles file and fill vector with riddles
    ifstream file_in(filename);
    if (file_in.fail()) {
        cout << "Riddle file doesn't exist." << endl;
        return;
    } else {
        cout << "Riddle file loading... ";
    }

    string currentText = "", currentLine = "";
    getline (file_in, currentLine);

    while (getline(file_in, currentLine)) {
        stringstream linestream (currentLine);
        int idx = 0;

        Riddles currentRiddle;

        while (getline(linestream, currentText, '|')) {
            if (idx == 0) {
                currentRiddle.riddle=currentText;
                idx ++;
            } else if (idx == 1) {
                currentRiddle.answer=currentText;
                _riddles.push_back(currentRiddle);
                idx = 0;
            }
        }
    }

    cout << "file loaded!" << endl;
}

//menu functions, selectors, similar
Characters Game::characterSelect() {
    cout << "Time to chose a character! We have the following avalible!" << endl;
    int vector_size = _characters.size(), userIn = 0;
    for (int i = 0; i < vector_size; i++) {
        cout << "Character " << i+1 << "    " <<  _characters[i].name << ", age " << _characters[i].age << endl
             << "Strength: " << _characters[i].strength << "  Stamina: " << _characters[i].stamina << "  Wisdom: " << _characters[i].wisdom << endl;
        cout << "-------" << endl;
    }
    while (userIn <= 0 || userIn > vector_size) {
        cout << "Choose from characters 1 to " << vector_size << endl;
        cin >> userIn;
    }

    Characters chosen_char = _characters[userIn-1];

    return chosen_char;
}

Advisor Game::advisorSelect() {
    cout << "Time to chose a advisor! We have the following avalible!" << endl;

    int vector_size = _advisors.size(), userIn = 0;

    for (int i = 0; i < vector_size; i++) {
        cout << "Advisor " << i+1 << "    " << _advisors[i].name << endl
             << "Ability: " << _advisors[i].ability << endl
             << "Description: " << _advisors[i].abilityDesc << endl;
    }
    while (userIn <= 0 || userIn >= vector_size) {
        cout << "Choose from advisors (1 to " << vector_size << ")" << endl;
        cin >> userIn;
    }

    Advisor chosen_advisor = _advisors[userIn-1];

    return chosen_advisor;
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
            cout << "Under Construction!" << endl;
            /*Enter saved game name:" << endl;
            cin >> input;
            filename += input;
            filename += ".save";
            loadGame(filename);
            */
            break;
            case 3:
            highScore();
            break;
            case 4:
            cout << "Thanks for playing!" << endl;
            break;
            default:
            cout << "Invalid input, try again!";
            break;
        }
    }
}

void Game::event(int player) {
    int eventSize, eventChooser;
    Events chosenEvent;
    if (_players[player].getBoardType() == 0) {
        eventSize = _norm_events.size();
        eventChooser = rand()%eventSize;
        chosenEvent = _norm_events[eventChooser];
    } else {
        eventSize = _easy_events.size();
        eventChooser = rand()%eventSize;
        chosenEvent = _easy_events[eventChooser];
    }
    cout << chosenEvent.event << endl;

    if (chosenEvent.points < 0) {
        //bad things
        if (chosenEvent.advisor == 0) {
            cout << "Nothing you can do can stop this. You lose " << chosenEvent.points << " points." << endl;
            _players[player].changePoints(chosenEvent.points);
        } else if (chosenEvent.advisor == 1 && _players[player].getPlayerAdvisor().name == "Rafiki") {
            cout << "Rafiki uses his powers of invisibility to save you!" << endl;
        } else if (chosenEvent.advisor == 2 && _players[player].getPlayerAdvisor().name == "Nala") { 
            cout << "Nala uses her power of night vision to save you!" << endl;
        } else if (chosenEvent.advisor == 3 && _players[player].getPlayerAdvisor().name == "Sarabi") {
            cout << "Sarabi uses her powers of energy manipulation to save you!" << endl;
        } else if (chosenEvent.advisor == 4 && _players[player].getPlayerAdvisor().name == "Zazu") {
            cout << "Zazu uses his powers of weather control to save you!" << endl;
        } else if (chosenEvent.advisor == 5 && _players[player].getPlayerAdvisor().name == "Sarafina") {
            cout << "Sarafina uses her power of super speed to save you!" << endl;
        } else {
            _players[player].changePoints(chosenEvent.points);
            cout << "You lose " << chosenEvent.points << " points!";
        }
    } else {
        //good things
        cout << "You gain " << chosenEvent.points << " points!";
        _players[player].changePoints(chosenEvent.points);
    }
    return;
}

void Game::riddleEncounter(int player) {
    string userAnswer = "";
    int riddleSize = _riddles.size();
    int riddleChooser = rand()%riddleSize;

    cout << "You must solve a riddle to continue!" << endl << _riddles[riddleChooser].riddle << endl;
    cin >> userAnswer;

    string riddleAnswer = _riddles[riddleChooser].answer;
    riddleAnswer += "\n";

    if (userAnswer == riddleAnswer) {
        cout << "Huzzah! You are correct!" << endl;
        _players[player].changeWisdom(500);
    } else {
        cout << "Tragically, you have failed. The correct answer was " << _riddles[riddleChooser].answer << endl;
    }
}

void Game::gameOver() {
    cout << "Congrats on reaching the end of the game!" << endl;
    ofstream record_Score("input_files/highscore.txt");
    int playerSize = _players.size();

    //year_month_day ymd{chrono::floor<chrono::days>(now)};

    for (int i = 0; i < playerSize; i++) {
        cout << "Player " << i+1 << "'s score is: " << _players.at(i).getPoints() << endl;

        record_Score << _players.at(i).getPlayerName() << "|" << _players.at(i).getPoints() << endl;
    }

    cout << "Thank you for playing! Taking you back to the main menu..." << endl;
}

void Game::highScore() {
    //brings in the highscore text
    ifstream recordScores("input_files/highscore.txt");
    if (recordScores.fail()) {
        cout << "High score file failed to load." << endl; 
        return;
    } else {
        cout << "High score file successfully loaded!" << endl;
    }

    //declares some stuff we're gonna use later
    string currentLine = "";
    vector<Score> scoreboard;
    int playerIndex = 0;

    //parses the file, and fills the vector scoreboard with all the scores in the highscore file.
    while (getline(recordScores, currentLine)) {
        stringstream linestream(currentLine);
        string playerName = "";
        int playerScore = 0;
        string currentIn = "";
        Score currentScore;

        while(getline(linestream, currentIn, '|')){
            if (playerIndex == 0) {
                playerName = currentIn;
                currentScore.name = playerName;
                playerIndex++;
            } else {
                playerScore = stoi(currentIn);
                currentScore.points = playerScore;
                scoreboard.push_back(currentScore);
                playerIndex = 0;
            }
        }
    }

    //quick bubble sort
    int boardSize = scoreboard.size();
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize-1; j++) {
            if (scoreboard.at(j).points < scoreboard.at(j+1).points) {
                swap (scoreboard[j], scoreboard[j+1]);
            }
        }
    }

    cout << "The top 10 players of all time are:" << endl
         << "Name:           - Points:" << endl;

    for (int i = 0; i < 10 && i < boardSize; i++) {
        string output = scoreboard[i].name;
        if (output.length() > 15) {
            while (output.length() > 15) {
                output.pop_back();
            }
        } else if (output.length() < 15) {
            while (output.length() < 15) {
                output.append(" ");
            }
        }
        
        cout << output << " -  " << scoreboard[i].points << endl;
    }

    return;
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


//useless stuff for now, but it's basically a save game constructor:
/*
Game::Game(int playerNumber, string eventsFile, string advisorFile, string characterFile, string riddleFile) {
    advisorPuller(advisorFile);
    eventPuller(eventsFile);
    characterPuller(characterFile);
    riddlePuller(riddleFile);
    //all of these beautiful things, declared!
    //_players;
    int _player_arr[2][2];

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

    gameMasterInit();

    return;
}
*/