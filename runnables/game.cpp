#include<csignal>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<ostream>
#include<sstream>
#include<string>

#include"../headers/game.h"
#include"../headers/spinner.h"
#include"../headers/Board.h"
#include"../headers/score.h"
#include"../headers/input_san.h"
#include"../headers/enemy.h"

using namespace std;
/* The Game function is the internal & main function.

Currently, I have functions to:
- split the text files up into vectors of characters, advisors, riddles, and events.

Variables, I have:
- vectors of players, characters, advisors, riddles, and events.

Initialization starts in constructor, and then we hit the menu, which activates GameMaster Init.

Turns follow this proess: gamemaster activates turn, which returns the next player int, which gamemaster feeds back into turn,
until it recieves -1 and does game-over

Turn does event management, movement, and so forth. If I had more time, Turn would have been broken up into two or three more functions, likely/

GameOver (should) take the point totals of all characters and add them to 
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

    return;
}

//Gameplay functions - start game, manage game, run turns
void Game::gameMasterInit () {
    cout << endl;
    int playerNum = 0, boardSelect=0;
    while (playerNum > 5 || playerNum <= 0) {
        cout << "Enter number of players (up to 5)" << endl;
        playerNum = input_san();
        if (playerNum > 5) {
            cout << "please double check your maths." << endl;
        }
    }

    for (int i = 0; i < playerNum; i++) {
        cout << "Player " << i+1 << "... let's get you started." << endl;
        cout << "Select difficulty: normal (1) or easy (2)?" << endl;
        boardSelect = input_san();

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

    Board newBoard(_players);
    newBoard.initializeBoard();
    _theBoard = newBoard;
    _theBoard.displayBoard();
    //_theBoard.getVectorSize();
    gameMaster();
}

void Game::gameMaster () {
    int player = 0;
    while ((player=turn(player)) != -1);
    gameOver();
    mainMenu();
}

int Game::turn (int player) {
    //declaring variables...
    Player currentPlayer = _players.at(player);
    int numPlayers = _players.size();
    char tileType;
    int userIn;
    int winners = 0;

    if (winners == numPlayers) {
        return -1;
    }

    currentPlayer.menu();

    int move_distance = spinner();

    //We're doing all the move stuff here...
    tileType = _theBoard.movePlayer(player, move_distance);
    cout << "Tile type is " << tileType << endl;
    currentPlayer.move(move_distance);
    _theBoard.displayBoard();


    //Tile type chars are: O (last block), Y (first block), G (grasslands), P (advisor), U (challenge), R (graveyard), N (hyena), B (oasis)
    cout << endl << "Landed on a ";
    if (tileType == 'O') {
        cout << "victory tile! Congrats!" << endl;
        winners++;
        if (numPlayers == 1) {
            return -1;
        } else if (winners >= numPlayers) {
            return -1;
        } else if (player == numPlayers-1) {
            cout << "It's now player 1's turn." << endl;
            return 0;
        } else {
            cout << "It's now player " << player+2 << "'s turn." << endl;
            return player+1;
        }

    } else if (tileType == 'G') {
        cout << "grasslands tile. ";
        if (spinner()%2 == 0) {
            event(player);
        } else {
            cout << "You may rest this turn." << endl;
        }

    } else if (tileType == 'P') {
        cout << "advisor tile. You feel greatly rested, and suddently quite wise. " << endl;;
        userIn = 0;

        currentPlayer.changeWisdom(300);
        currentPlayer.changeStamina(300);
        currentPlayer.changeStrength(300);

        while (userIn < 1 || userIn > 2) {
            cout << "Do you wish to pick a new advisor? 1 for yes, 2 for no, 3 to see current advisor" << endl;
            cin.clear();
            cin >> userIn;
            if (userIn == 1) {
                _advisors.push_back(currentPlayer.getPlayerAdvisor());
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
        cout << "a riddle tile! Prepare to be bewitched! " << endl;
        riddleEncounter(player);
    } else if (tileType == 'R') {
        cout << "a graveyard tile. The sights, the smells, are terrible. You faint and wake up 10 tiles back." << endl;
        int movement = -10;
        currentPlayer.move(movement);
        _theBoard.movePlayer(player, movement);
        //This forces the player to move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points.
        currentPlayer.changeWisdom(-100);
        currentPlayer.changeStamina(-100);
        currentPlayer.changeStrength(-100);
    } else if (tileType == 'N') {
        cout << "hyena tile. Be careful! " << endl;
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
    cout << "Player " << player+1 << "'s turn is over." << endl;
    if (player == numPlayers-1) {
        cout << "It's now player 1's turn." << endl;
        return 0;
    } else {
        cout << "It's now player " << player+2 << "'s turn." << endl;
        return player+1;
    }
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
    int vector_size = _characters.size(), userChoose = 0;
    string userIn = "";
    for (int i = 0; i < vector_size; i++) {
        cout << "Character " << i+1 << "    " <<  _characters[i].name << ", age " << _characters[i].age << endl
             << "Strength: " << _characters[i].strength << "  Stamina: " << _characters[i].stamina << "  Wisdom: " << _characters[i].wisdom << endl;
        cout << "-------" << endl;
    }
    while (userChoose <= 0 || userChoose > vector_size) {
        cout << "Choose from characters 1 to " << vector_size << endl;
        userChoose = input_san();
    }

    Characters chosen_char = _characters[userChoose-1];
    _characters.erase(_characters.begin()+(userChoose-1));

    return chosen_char;
}
Advisor Game::advisorSelect() {
    cout << "Time to chose a advisor! We have the following avalible!" << endl;

    int vector_size = _advisors.size(), userChoose = 0;

    for (int i = 0; i < vector_size-1; i++) {
        cout << "Advisor " << i+1 << "    " << _advisors[i].name << endl
             << "Ability: " << _advisors[i].ability << endl
             << "Description: " << _advisors[i].abilityDesc << endl;
    }
    while (userChoose <= 0 || userChoose > vector_size) {
        cout << "Choose from advisors (1 to " << vector_size << ")" << endl;
        userChoose = input_san();
    }

    Advisor chosen_advisor = _advisors[userChoose-1];
    _advisors.erase(_advisors.begin() + (userChoose-1));

    return chosen_advisor;
}
void Game::mainMenu() {
    string userIn = "";
    int userNum = 0;
    string filename = "../saved/",input;
    while (userNum != 3) {
        cout << "Menu options (select by number):" << endl
             << "1. New Game" << endl
             << "2. High Score" << endl
             << "3. Exit Game" << endl;
        userNum = input_san();

        switch (userNum) {
            case 1:
            gameMasterInit();
            break;
            case 2:
            cout << "Under Construction!" << endl;
            highScore();
            break;
            case 3:
            cout << "Thanks for playing!" << endl;
            break;
            default:
            cout << "Invalid input, try again!";
            break;
        }
    }
}
//event management
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
            cout << "You lose " << chosenEvent.points << " points!" << endl;
        }
    } else {
        //good things
        cout << "You gain " << chosenEvent.points << " points!" << endl;
        _players[player].changePoints(chosenEvent.points);
    }
    return;
}
void Game::riddleEncounter(int player) {
    string userAnswer = "";
    int riddleSize = _riddles.size();
    int riddleChooser = rand()%riddleSize;

    cout << "You must solve a riddle to continue!" << endl << _riddles[riddleChooser].riddle << endl;
    cin.clear();
    cin >> userAnswer;

    string riddleAnswer = _riddles[riddleChooser].answer;
    //riddleAnswer += "\n";

    if (userAnswer == riddleAnswer) {
        cout << "Huzzah! You are correct!" << endl;
        _players[player].changeWisdom(500);
    } else {
        cout << "Tragically, you have failed. You entered '" << userAnswer << "' and the correct answer was '" << riddleAnswer << "'" << endl;
    }
}
void Game::gameOver() {
    cout << "Congrats on reaching the end of the game!" << endl;
    ofstream record_Score("input_files/highscore.txt", ios::app);
    int playerSize = _players.size();

    //year_month_day ymd{chrono::floor<chrono::days>(now)};

    for (int i = 0; i < playerSize; i++) {
        cout << "Player " << i+1 << "'s score is: " << _players.at(i).gameOver() << endl;
        record_Score << _players.at(i).getPlayerName() << "|" << _players.at(i).gameOver() << endl;
    }
//adjust for new player as vector
    if (playerSize >= 2) {
        if (_players.at(0).gameOver() > _players.at(1).gameOver()) {
            cout << "Congrats! Player 1 has won!" << endl;
        } else if (_players.at(0).gameOver() < _players.at(1).gameOver()) {
            cout << "Congrats! Player 2 has won!" << endl;
        } else {
            cout << "There must be some mistake, you appear to have tied. Play again to see who has the best luck!" << endl;
        }
    }
    cout << "Thank you for playing! Printing highscores and taking you back to the main menu..." << endl;
    highScore();
    return;
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
void Game::combat(int player, int scenario) {
    int attackTurn = 0, defenseTurn = 0, healthChange = 0;

    //battle stats!
    int playerAttack, playerDefense, playerHealth;
    Enemy badguy;
    playerAttack = (_players.at(player).getStrength())/100;
    playerDefense = (_players.at(player).getWisdom())/100;
    playerHealth = (_players.at(player).getStamina())/100;

    badguy.attack = (rand() % ((playerAttack+2) + 1 - (playerAttack-3)) + (playerAttack-3));
    badguy.defense = (rand() % ((playerDefense+2) + 1 - (playerDefense-3)) + playerAttack-3);
    badguy.health = (rand()% (5 - 1) + 1);

    if (badguy.attack <= 0) {
        badguy.attack = 1;
    }
    if (badguy.defense <= 0) {
        badguy.defense = 0;
    }

    while (badguy.health > 0 && playerHealth > 0) {
        cout << "Combat encounter!" << endl
             << "         Hyena:        Player:" << endl
             << "ATK    : " << badguy.attack <<  "        " << playerAttack << endl
             << "DEF    : " << badguy.defense << "        " << playerDefense << endl
             << "Health : " << badguy.health << "        " << playerHealth << endl;

        cout << "Attack (1), Sacrifice Advisor (2), or Die (3):" << endl;
        int menu = input_san();

        if (menu == 1) {
            cout << "You rolled a ";
            for (int i = 0; i < playerAttack; i++) {
                attackTurn += spinner();
            }
            cout << attackTurn << "!" << endl;
            cout << "The hyena rolled a ";
            for (int i = 0; i < badguy.defense; i++) {
                defenseTurn += spinner();
            }
            cout << defenseTurn << " on defense, and took ";
            healthChange = defenseTurn-attackTurn;
            if (healthChange < 0) {
                cout << -healthChange << " damage!";
                badguy.health += healthChange;
            } else {
                cout << " no damage!" << endl;
            }
            //now for the defensive side!
            cout << "The hyena attacks!" << endl;
            attackTurn = 0;
            defenseTurn = 0;
            healthChange = 0;

            cout << "The hyena rolled a ";
            for (int i = 0; i < badguy.attack; i++) {
                attackTurn += spinner();
            }
            cout << attackTurn << "!" << endl;
            cout << "You rolled a ";
            for (int i = 0; i < playerDefense; i++) {
                defenseTurn += spinner();
            }
            cout << defenseTurn << " for defense, and took ";
            healthChange = defenseTurn-attackTurn;
            if (healthChange < 0) {
                cout << -healthChange << " damage!";
                playerHealth += healthChange;
            } else {
                cout << " no damage!" << endl;
            }
        } else if (menu == 2) {
            if (_players.at(player).getPlayerAdvisor().name == "") {
                cout << "Not a option!" << endl;
            } else {
                badguy.health = 0;
                Advisor blankAdvisor;
                _players.at(player).setAdvisor(blankAdvisor);
            }
        } else if (menu == 3) {
            playerHealth = 0;
        }
    }

    if (badguy.health <= 0) {
        cout << "You must have won this encounter... you may stay on this tile." << endl;
    } else if (playerHealth <= 0) {
        cout << "You have lost this encounter, prepare to move back." << endl;
        _players.at(player).move(-10);
        _theBoard.movePlayer(player, -10);
    }
    return;
}