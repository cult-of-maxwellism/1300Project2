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
" ______     ______   ______     ______     ______                           \n"
"/\\  ___\\   /\\  == \\ /\\  __ \\   /\\  ___\\   /\\  ___\\                          \n"
"\\ \\___  \\  \\ \\  _-/ \\ \\  __ \\  \\ \\ \\____  \\ \\  __\\                          \n"
" \\/\\_____\\  \\ \\_\\    \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\                        \n"
"  \\/_____/   \\/_/     \\/_/\\/_/   \\/_____/   \\/_____/                        \n";
    artwork();
    cout <<
" ______     ______     __         __   __   ______     ______     ______    " << endl <<
"/\\  ___\\   /\\  __ \\   /\\ \\       /\\ \\ / /  /\\  __ \\   /\\  ___\\   /\\  ___\\   " << endl <<
"\\ \\___  \\  \\ \\  __ \\  \\ \\ \\____  \\ \\ \'/   \\ \\  __ \\  \\ \\ \\__ \\  \\ \\  __\\   " << endl <<
" \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\__|    \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\ " << endl <<
"  \\/_____/   \\/_/\\/_/   \\/_____/   \\/_/      \\/_/\\/_/   \\/_____/   \\/_____/ " << endl;

    int spin = rand()%2;
    switch (spinner()+(spin-1)) {
        case 0:
        cout << "Ain’t No Power in the ’Verse Like a Good Salvage Run." << endl;
        break;
        case 1:
        cout << "These are the droids you're looking for." << endl;
        break;
        case 2:
        cout << "In Space, No One Can Hear You Strip a Derelict." << endl;
        break;
        case 3:
        cout << "If I was running the company in Hardspace: Shipbreaker, I would have simply cut off oxygen supplies to the striking miners. Seriously, these guys try to tell a gritty story about the power of unions (and the struggles of unionizing) and the best they can come up with for the bad guys to do is, like, fire a middle manager. No one loses food privledge, seriously?" << endl;
        break;
        case 4:
        cout << "Live Long and Prosper!" << endl;
        break;
        case 5:
        cout << "Explore, Expand, Exploit and Exterminate." << endl;
        break;
        default:
        cout << "Your mom definitely approves." << endl;
    }
    cout << endl << "+++ +++ +++ +++ +++ +++ +++ +++ +++" << endl;
    cout << endl << endl;

    return;
}

//Gameplay functions - start game, manage game, run turns
void Game::gameMasterInit () {
    cout << endl;
    int playerNum = 0, boardSelect=0;
    while (playerNum > 5 || playerNum <= 0) {
        cout << "Enter number of players (up to 5)" << endl; //this limit is artifical, up to a theoretical infinite!
        playerNum = input_san();
        if (playerNum > 5) {
            cout << "please double check your maths." << endl;
        }
    }

    for (int i = 0; i < playerNum; i++) {
        cout << "Player " << i+1 << "... let's get you started." << endl;
        cout << "Select difficulty: hard (1) or easy (2)?" << endl;
        boardSelect = input_san();

        boardSelect--;

        cout << endl << "+----+----+----+----+----+----+----+" << endl;
        Characters temp_char = characterSelect();
        cout << endl << "+----+----+----+----+----+----+----+" << endl;

        Player temp(i, temp_char, boardSelect);

        cout << endl << "+----+----+----+----+----+----+----+" << endl;
        if (boardSelect == 1) {
            cout << "Since you have selected the easier difficulty, please select an consultant - they'll help you through the game." << endl;
            cout << endl << "+----+----+----+----+----+----+----+" << endl;
            Advisor temp_advise = advisorSelect();
            cout << endl << "+----+----+----+----+----+----+----+" << endl;
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

    cout << endl << "+----+----+----+----+----+----+----+" << endl;
    Board newBoard(_players);
    newBoard.initializeBoard();
    _theBoard = newBoard;
    _theBoard.displayBoard();
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

    if (currentPlayer.getWinCond()==true){
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
    }

    currentPlayer.menu();

    int move_distance = spinner();

    //We're doing all the move stuff here...
    tileType = _theBoard.movePlayer(player, move_distance);
    currentPlayer.move(move_distance);
    _theBoard.displayBoard();
    cout << "You've gone " << move_distance << " distance." << endl;

    //here's the event management!

    //Tile type chars are: O (last block), Y (first block), G (grasslands), P (advisor), U (challenge), R (graveyard), N (hyena), B (oasis)cout << "at idx 5";
    cout << endl << "You make your way further into space, in search of salvage, and happen across: ";
    if (tileType == 'O') { //last block
        cout << endl;
        planetArt();
        int ending = rand()%4;
        switch (ending) {
            case 0: 
            cout << "a perfect marketplace to sell your salvage. Congratulations!" << endl;
            break;
            case 1:
            cout << "one of Lovecraft's old ones. Apparently, Yog-suggoth is a huuuge fan of salvage, so he'll take yours from ya!" << endl;
            break;
            case 2:
            cout << "a really dreary marketplace, pretty damp and it smells. However, there's a zarblaxian collector who will pay top dollar for your salvage!" << endl;
            break;
            case 3:
            cout << "your mother's house. She offers to buy your salvage at above market rates, if you agree to come back. She loves you very much." << endl;
            break;
            case 4:
            cout << "a rowdy group of aliens. They beat you up and take your salvage. Later, you discover plenty of cash in your pocket, and you realize they were just really eager to get a deal done." << endl;
            break;
        }
        //just need to make sure I don't add too many winners!
        if (currentPlayer.getWinCond() == false) {
            winners++;
            currentPlayer.setWinCond(true);
        }

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

    } else if (tileType == 'G') { //"grasslands"
        cout << "an asteroid field. ";
        if (spinner()%2 == 0) {
            event(player);
        } else {
            cout << "There's nothing here to salvage or fight, and you may rest this turn." << endl;
        }

    } else if (tileType == 'P') { //"advisors"
        cout << "consultancy firm. You feel greatly rested, and suddently quite wise. This place is full of people who'd love to help on your journey." << endl;;
        userIn = 0;

        currentPlayer.changeWisdom(300);
        currentPlayer.changeStamina(300);
        currentPlayer.changeStrength(300);

        while (userIn < 1 || userIn > 2) {
            cout << "Do you wish to pick a new consultant? 1 for yes, 2 for no, 3 to see current consultant" << endl;
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
                cout << "Consultant: " << playerAdvisor.name << " Ability: " << playerAdvisor.ability << endl << "Ability Description" << playerAdvisor.abilityDesc << endl;
            }
        }
    } else if (tileType == 'U') { //challenge
        cout << "a locked crate, floating in space. Next to the keypad lock is a single riddle..." << endl;
        riddleEncounter(player);
    } else if (tileType == 'R') { //graveyard/reaver attack
        cout << "a unsalvageable ship, destroyed by the reavers. The sights, the smells, are terrible. You run 10 tiles back - hopefully, you've outrun the reavers that did this." << endl;
        int movement = -10;
        currentPlayer.move(movement);
        _theBoard.movePlayer(player, movement);
        //This forces the player to move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points.
        currentPlayer.changeWisdom(-100);
        currentPlayer.changeStamina(-100);
        currentPlayer.changeStrength(-100);
    } else if (tileType == 'N') { // "hyena"/violence!
        cout << "a ship which suddenly attacks you! " << endl;
        int scenario = spinner();
        attackArt(scenario);
        combat(player, scenario);
    } else if (tileType == 'B') { // salvage!
        cout << endl;
        spaceArt();
        switch (spinner()) {
            case 0:
            //if you get this case, you just get double the stam/wis/str bonus
            cout << "an ancient, autonomous, Bhuddist exploration vessel. You feel quite rested, but there's nothing to salvage here." << endl;
            currentPlayer.changeStamina(200);
            currentPlayer.changeStrength(200);
            currentPlayer.changeWisdom(100);
            break;
            case 1:
            cout << "an ancient, derelict Mormon colony ship, drifting silently through the void. Its systems hum with barely noticeable energy. You feel a mild unease creep over you, as though something is watching. Your nerves are on edge..." << endl;
            currentPlayer.changeSalvage(700);
            cout << "These things were massive and full of salvageable items! You find 700, exellent condition, pieces of salvage." << endl;
            break;
            case 2:
            cout << "an old, autonomous Spacer's Guild freighter, floating quietly in the cold expanse. The ship seems abandoned, yet the low hum of ancient machinery resonates like a warning. You can almost feel the presence of something otherworldly lurking in the shadows." << endl;
            currentPlayer.changeSalvage(800);
            cout << "These old Spacer's Guild ships are chock-full of good material. You find 800 pieces of sellable salvage." << endl;
            break;
            cout << "a shockingly modern racing ship, in a decaying orbit around a nearby moon. It doesn't respond to hails, and no life signs are present. Plugging power into the computer, you discover the occupants accidentally spaced themselves during a poorly planned game of drunk electro-ball." << endl;
            currentPlayer.changeSalvage(300);
            cout << "You find 300 items that you could sell at a good price." << endl;
            case 3:
            cout << "an abandoned Higaran mothership, from before the Great War. Many thousands of people used to serve on these, but it's been centuries, and it's quite clear you're alone. Despite this, you still feel warm and comforted." << endl;
            currentPlayer.changeSalvage(500);
            cout << "You find 500 pieces of good salvage." << endl;
            break;
            case 4:
            cout << "a mysterious, ancient Terran survey vessel, drifting through space, its purpose long forgotten. The interior is unnervingly quiet, and the dim lights flicker erratically. You can’t shake the feeling that something is wrong here, as if the ship has a secret it’s trying to keep." << endl;
            currentPlayer.changeSalvage(200);
            break;
            case 5:
            cout << "a colossal, silent warship from the Elysian Star Empire, hanging motionless in the void. The ship is massive, and its dark, lifeless corridors seem to pulse with an oppressive, ominous energy. Every step you take feels like you’re walking deeper into a trap." << endl;
            cout << "You find weapons, command consoles, and chairs, amounting to 400 pieces of salvage." << endl;
            currentPlayer.changeSalvage(400);
            break;
            case 6:
            cout << "a rusted and forgotten mercenary transport ship, adrift in the dark reaches. The bodies of some of the former crew float nearby, victims of what appears to have been a power struggle on board. The ship feels defiant.";
            currentPlayer.changeSalvage(100);
            cout << "You find a few rusted weapons. As you turn to leave, dejectedly, the a box with the Captian's logo on it catches your eye. It's full of precious metals: not enough to be lifechanging, but enough nonetheless." << endl << "You gain 100 salvage items." << endl;
            break;
            default:
            //if you get this case, you just get double the stam/wis/str bonus
            cout << "an ancient, autonomous, Bhuddist exploration vessel. You feel quite rested, but there's nothing to salvage here." << endl;
            currentPlayer.changeStamina(200);
            currentPlayer.changeStrength(200);
            currentPlayer.changeWisdom(100);
        }
        //200 Stamina, Strength, and Wisdom Points.
        currentPlayer.changeStamina(200);
        currentPlayer.changeStrength(200);
        currentPlayer.changeWisdom(100);
    }
    cout << "Player " << player+1 << "'s turn is over." << endl
         << "+-------------+-------------+" << endl;
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
        int idx = 0, currentNum = 0;

        Advisor currentAdvisor;

        while (getline(linestream, currentText, '|')) {
            if (idx == 0) {
                currentNum = stod(currentText);
                currentAdvisor.num = currentNum;
                idx ++;
            } else if (idx == 1) {
                currentAdvisor.name=currentText;
                idx++;
            } else if (idx == 2) {
                currentAdvisor.ability=currentText;
                idx ++;
            } else if (idx == 3) {
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
    cout << "Reached char file" << endl;
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
                idx++;
            } else if (idx == 6) {
                currentCharacter.bio=currentText;
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
             << "Strength: " << _characters[i].strength << "  Stamina: " << _characters[i].stamina << "  Wisdom: " << _characters[i].wisdom << endl
             << "Bio: " << _characters[i].bio << endl;
        cout << "-------" << endl;
    }
    while (userChoose <= 0 || userChoose > vector_size) {
        cout << "Choose from characters 1 to " << vector_size << endl;
        userChoose = input_san();
    }

    //This picks out the character the user chooses, and deletes said character from the characters vectors
    Characters chosen_char = _characters[userChoose-1];
    _characters.erase(_characters.begin()+(userChoose-1));

    return chosen_char;
}
Advisor Game::advisorSelect() {
    cout << "Time to chose a advisor! We have the following avalible!" << endl;

    int vector_size = _advisors.size(), userChoose = 0;

    cout << "advisor size: " << vector_size << endl;

    for (int i = 0; i < vector_size-1; i++) {
        cout << "Advisor " << i+1 << ":    " << _advisors[i].name << endl
             << "Ability: " << _advisors[i].ability << endl
             << "Description: " << _advisors[i].abilityDesc << endl;
        cout << "-------" << endl;
    }
    while (userChoose <= 0 || userChoose > vector_size) {
        cout << "Choose from advisors (1 to " << vector_size << ")" << endl;
        userChoose = input_san();
    }

    // this here sets the advisor the user choses, and deletes the advisor from the Advisors vector, to make sure no one else can use that Advisor.
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
        } else if (chosenEvent.advisor == _players[player].getPlayerAdvisor().num) {
            cout << "Your consultant used their skills to save you!" << endl;
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

    cout << "You must solve this riddle to continue!" << endl << _riddles[riddleChooser].riddle << endl;
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
    ofstream record_Score("input_files/highscore.txt", ios::app);
    int playerSize = _players.size();
    int maxScore = 0;
    int winner = -1;
    bool tie = false;
    
    cout << "Congrats on reaching the end of the game!" << endl;
    //calculate who won
    for (int i = 0; i < playerSize; ++i) {
        int score = _players.at(i).gameOver();
        if (score > maxScore) {
            maxScore = score;
            winner = i;
            tie = false;
        } else if (score == maxScore) {
            tie = true;
        }
    }

    //run everything again to get an idea of who's got what score
    for (int i = 0; i < playerSize; i++) {
        cout << "Player " << i+1 << "'s score is: " << _players.at(i).gameOver() << endl;
        record_Score << _players.at(i).getPlayerName() << "|" << _players.at(i).getCharName() << "|" << _players.at(i).gameOver() <<endl;
    }
    
    //and do the victory logic!
    if (tie) {
        switch (rand()%2) {
            case 0:
            cout << "We've always known y'all are equally matched. Better luck next time!" << endl;
            case 1:
            cout << "It’s a tie. No winners here. Back to the drawing board." << endl;
            break;
            case 2:
            cout << "There must be some mistake, you appear to have tied. Play again to see who has the best luck!" << endl;
            break;
            default: 
            cout << "No ties allowed. You MUST play again." << endl;
        }
    } else if (winner != -1) {
        cout << "Congrats! Player " << winner+1 << " has won!" << endl;
    }

    //final message!
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
            } else if (playerIndex == 1) {
                currentScore.charName = currentIn;
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
         << "Name:           Character: - Points:" << endl;

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

        string output2 = "(as ";
        output2 += scoreboard[i].charName;
        output2 += ")";
        if (output2.length() > 10) {
            while (output2.length() > 10) {
                output2.pop_back();
            }
        } else if (output2.length() < 10) {
            while (output2.length() < 10) {
                output2.append(" ");
            }
        }
        
        cout << output << output2 << " -  " << scoreboard[i].points << endl;
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
    playerHealth = (_players.at(player).getStamina())/50;

    badguy.attack = (rand() % ((playerAttack+5) + 1 - (playerAttack-3)) + (playerAttack-3));
    badguy.defense = (rand() % ((playerDefense+4) + 1 - (playerDefense-3)) + playerAttack-3);
    badguy.health = (rand()% (5 - 1) + 1);

    if (badguy.attack <= 0) {
        badguy.attack = 1;
    }
    if (badguy.defense <= 0) {
        badguy.defense = 0;
    }

    while (badguy.health > 0 && playerHealth > 0) {
        //I was planning on adding different possible bad guys, but ran out of energy.
        cout << "Combat encounter!" << endl
             << "         Alien:      Player:" << endl;
        //attack stats
        string output1 = to_string(badguy.attack);
        while (output1.length() < 12) {
            output1+= " ";
        }
        cout << "ATK    : " << badguy.attack <<  "        " << playerAttack << endl;
        //def
        output1 = to_string(badguy.defense);
        while (output1.length() < 12) {
            output1+= " ";
        }
        cout << "DEF    : " << badguy.defense << "        " << playerDefense << endl;
        //health
        output1 = to_string(badguy.health);
        while (output1.length() < 12) {
            output1+= " ";
        }
        cout << "Health : " << badguy.health << "        " << playerHealth << endl;

        cout << "Attack (1), Sacrifice Advisor (2), or Die (3):" << endl;
        int menu = input_san();

        if (menu == 1) {
            cout << "You rolled a ";
            for (int i = 0; i < playerAttack; i++) {
                attackTurn += spinner();
            }
            cout << attackTurn << "!" << endl;
            cout << "The aliens rolled a ";
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
            cout << "The aliens attack!" << endl;
            attackTurn = 0;
            defenseTurn = 0;
            healthChange = 0;

            cout << "The alien rolled a ";
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
                cout << "no damage!" << endl;
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
        _players.at(player).changeStamina((-(_players.at(player).getSalvage()/2)));
        _theBoard.movePlayer(player, -10);
    }
    return;
}

//art stuff!
void Game::artwork () {
    int choseArt = rand()%3;
    switch (choseArt) {
        case 0: 
        attackArt(spinner());
        break;
        case 1:
        spaceArt();
        break;
        case 2:
        planetArt();
        break;
        case 3:
        planetArt();
        break;
        default:
        spaceArt();
    }
}
void Game::attackArt(int scenario) {
    //I was planning on adding different possible bad guys, but ran out of energy.
    switch (scenario) {
        case 1:
    cout << "Aliens!!!" << endl <<
"     _                      _______                      _" << endl <<
"  _dMMMb._              .adOOOOOOOOOba.              _,dMMMb_" << endl <<
" dP\'  ~YMMb            dOOOOOOOOOOOOOOOb            aMMP~  `Yb" << endl <<
" V      ~\"Mb          dOOOOOOOOOOOOOOOOOb          dM\"~      V" << endl <<
"          `Mb.       dOOOOOOOOOOOOOOOOOOOb       ,dM\'" << endl <<
"           `YMb._   |OOOOOOOOOOOOOOOOOOOOO|   _,dMP\'" << endl <<
"      __     `YMMM| OP\'~\"YOOOOOOOOOOOP\"~`YO |MMMP\'     __" << endl <<
"    ,dMMMb.     ~~' OO     `YOOOOOP\'     OO `~~     ,dMMMb." << endl <<
" _,dP~  `YMba_      OOb      `OOO\'      dOO      _aMMP\'  ~Yb._" << endl <<
"             `YMMMM\\`OOOo     OOO     oOOO'/MMMMP\'" << endl <<
"     ,aa.     `~YMMb `OOOb._,dOOOb._,dOOO\'dMMP~\'       ,aa." << endl <<
"   ,dMYYMba._         `OOOOOOOOOOOOOOOOO\'          _,adMYYMb." << endl <<
"  ,MP\'   `YMMba._      OOOOOOOOOOOOOOOOO       _,adMMP'   `YM." << endl <<
"  MP\'        ~YMMMba._ YOOOOPVVVVVYOOOOP  _,adMMMMP~       `YM" << endl <<
"  YMb           ~YMMMM\\`OOOOI`````IOOOOO\'/MMMMP~           dMP" << endl <<
"   `Mb.           `YMMMb`OOOI,,,,,IOOOO\'dMMMP\'           ,dM\'" << endl <<
"     `\'                  `OObNNNNNdOO\'                   `\'" << endl <<
"                           `~OOOOO~\'   TISSUE"<< endl;
        break;
        default: 
        cout << "whoops" << endl;
    }
}
void Game::spaceArt() {
    int decide = spinner();
    if (decide == 1) {
        cout <<
"..   . .: .      .. .  .   .. .. ..... .  .. . .          : :    ..:       ........    .  ....      " << endl <<
"     .    ;.  ; :. .      .   .   . . .  ...;.    .. .    ;.+.. .. .     ..... ...:.  .. . .. .   ; " << endl <<
".  ..               .  . ...  .. :  .. .  ..   .  ... .  . . ..   . .  . .   . . ..&...      .&.    " << endl <<
"..   . .  .  :.. . . . .. ..   ..  . ...     . .     ... .       ;.  .         ....   .. . .  ...   " << endl <<
".   .     .  ; .      .   . . .   :    .    .:.  ;.  . .   . . :..  ..      ..       .      . .. .  " << endl <<
". .  .    x    .  . . . ..  .. . .    . .   .  .. . $x ..  ..  +  .  .. . ;.    ...++. ..   ;  .  .." << endl <<
"   .  .          . .    . . .   ...   .  .:..  .. . &&$.:. ..:.. .... ...  ..    .      .:      .  ." << endl <<
" .. .   .   . . .:   X .  . .  . .   .....    .: x..&&&;.......  .. .         .   .. ;.;       :    " << endl <<
"   .:.  . .  . .  ;. .. .: .. ;     ..    .. ......+&&&&....: ... .         . .&:&:. .              " << endl <<
"    . .     .    X .. :. .     .    +  .  $.  .  . .&&&xx..  ...  ..  .. ..   . .     .     .  .   ." << endl <<
"            .  .      . .& . ..     . . .&...  .++  &&&&Xx. xx...:     & .          ..     .        " << endl <<
"  .          :        X. .     .     ..  :.:..&&&&&&&&&X++&X&$xx.  .  X .      .   .    .     x     " << endl <<
".   :     .     ..  :. .       x;+x;..x .&&&&&&&&&&&&&&&&&&&&&XX&x  . &    .     . .          + .   " << endl <<
"          .     . .  .       Xx   .  .+.&&&&&&$+X+$$&&&&&&&&&&&$x&&x &X   .     .  .;: .          : " << endl <<
" .     x .      X   .   .. ..  .  . .. ;&X;X$$;X&&$&&+x&&&&&&&&&&&&&&&&$$    . ; . .+: .            " << endl <<
" :         $       $        ..     . &&&$$XxX&$&$$&;XX&&&&&$$$&&&&&&&&&&&&&&&x&&&X X ...   .  .     " << endl <<
"   .         .. ..      ..  .   . ..&&&&Xxx&&$&.x.&&&&&$&$ .&     ..&X  . :    ;&&&$  .             " << endl <<
"   ..      .        ..  .    . ..$&$$&&&X&XxxxXxxxX&&&&&x . .  ..    &  ..   ;.   $$       . ..+    " << endl <<
"     ..            x .. . .;&$&&&$$&&&x&XXX+X&x&$+xx&&&x. .          .X . .. .    X    .            " << endl <<
":               :    .  .&&&+&&&&&&&;X&&x$&X&$;&&XX&&&&+  .    . . .                     .  :       " << endl <<
"   .     .         .   &&&&$$$$&$$X&&&&&XxxXx;&&&X: &&+                    .    &    .     .  .     " << endl <<
"          .         $&X&&$X&&&&$&XX$X$$X$X&& x $:   &$  .    .  ..   .       .   +                  " << endl <<
"   .       .   .   X && &&&&&&&&&X&&&&&$   $.$  .; $x                   .     .      ;  $           " << endl <<
". :   .  .:&.     X .     xX&&$X&X  $    .   X     .     . .                 .           .          " << endl <<
"        .  ..    .;  :..              .                   ..      .    . .       +       . .   .  : " << endl <<
" .   . x+    ..    . ...   :            . .         .            .         +        X    .         +" << endl <<
"          .         .      ..             .        .       . .  . ..                            & . " << endl <<
".          . ;  .    .;.       :    . .. .. .         ..               .     .      ;           .   " << endl <<
"       .       &:  .  . .  ..        .   .  .      ..         .                 .     .            ." << endl <<
" ;             :       x...;  .            .     ..           ;.       ;.   . .  .     ; .          " << endl <<
"  .       .                             .  .    ;.$.. .                   .                      .. " << endl <<
"       +   .     .                      :+   ..  .               +     .     +         .      ;     " << endl <<
"                                            . .. .  .  .          +  .        .                     " << endl <<
"     +      . .              .          ; .& ..                                 .. +; ..: ; .+;;. . " << endl;  
    } else if (decide == 2) {
        cout <<
"›››››››››››››››———————{{{{íí{{í{{{{{————————————›››››››  ›                                          " << endl <<
"ÅgÞÞÇÇ666üüÏÏzzí{{{{{{{{í{ííííííííí{{{{———————››—››››››››                                           " << endl <<
"ÅÆÅÅÅÅÅÆÆÅÅÅgÅÆÅÆÅÅGGGÞÞÞÇÇ666üÏzzíííí{{{———————››››››››        ›                                   " << endl <<
"gÅGGÅÆÆÅÆÆgÅgÇÞÇÞGÆÅGÅGÇÇÞgGÆÆÆgGGGGGÞÞÇÇ6üüzí{————›››››       —{                                   " << endl <<
"ÆÆÆÆÆÆÆÆÆÅgÆÆÅGGGÅÆÅgÅÆÅgÅGGGÞGGÅGGÇggÅgÅgÅggÅÅÅGÞÞÇ6üÏzí——››  ——   ›                               " << endl <<
"ÅÅÅÅÆÅÅÅÞÞÞÅÞÆÆÅgÅÅgÅÆÅÆÆÆÆÆÏÆÅÅgGGGGÅÆÆgÅgGÅÆGggGgGGÅÞÇGggÞÞÞÞ—Ï—z{››                              " << endl <<
"ÅÅÅÅÅÅÅÅÅÅÆÆgGÅÅÅÆÅgÏÏ6ÞgÅgüízzzüüüÆÆÆÅÆGGgÇÇÇÞÞGGÅÅÅÆÆÅggÞ666Å—›—ÞÞ6GÞÞ6üÏzí—›     › ›› ›          " << endl <<
"gÅÅggggÞggGÅÅGü{z6íízzzííÏzzííízííígggÆÆÆÆGgÅgggggGÞggÇÏÅÅÅÆÆÞü{——{›{Ç6ÇüGGz6GÅggÇz—z—{í››{z›       " << endl <<
"GÞgGGÇ6ÇÇGÅÅÅ{íí{zzzí{íííííííÅGÆ6üÏÅÅÅÅÅÆÅgÆÆÆÆÆÆÅÅÅgÅÅgí{G6Ïzzz——{—í{ÇüÏÇÞGÏzzí{——›› ›ÞÞG6üzí{›    " << endl <<
"gggÅÅÅÅÅÅÅÅÅÅí{{{{{{{{í{ííÞÇüÏÇGÅÅÅÅÅÅÅÆÅÅÅÅÅÅÅgÆzÆÆÅÅí——›{g—Gz{››————›———›—————›—››  ÅGGÞÞGgÇÞGÇÇ6ü" << endl <<
"ÞGGÞGGgÞÇü6üÏÏü66ü6ÇGÞÞÇÇggÅGÞ6ÇÞÇGÅÅgÅÅgÅgÆÅÇ6gÅÅGÞ{—z—››{{ ›—————{—›————›————››— Þ6ÞÆÅÅÆGgGGÞÇÇÇÇG" << endl <<
"üüüüüÏÏÏÏÏÏÏÏüü6ÇÞÇÞÞÞGGGÞGgGgggÇÇÞÞgÞ6zízÏÏÞGggí{í›z››—{›—{{—{{—{{—›››—›› —{ ››   › ›ggÅgGGGggGGGGG" << endl <<
"ÞÇ6ÞÞÇÇ66666ü6ÇÇÇÞÞÇÞÞGÞÞÞÞÞ6GÆgüííízÏÇÇGÇÇGzÞÇÏí—››{{———Ï Þ{{{í—{› ›› ››››››——› ›   ÏÞGgGÞÇGÞ6G66Çg" << endl <<
"ÞÞÇÇÞÇÞÞÞÞÞÞÞÞÞÞÞÞÞGÞÞgGGGÅGüíííüGÅgÅGüÇüz{————í›—6G{ÞÞz{—{{{—{{—   ›››—› —————››—›gGGGgÅggGGüÞüüüü6" << endl <<
"ÇÞÞÞÞÞÇGÞÞÞÞÞÞÞÞÞÞÞÞÞÞgÆgÏ{{{üÅGÞ6üz{{———{{{{{{{{{————{{{——› ›— —í› ››Ï›——›———GÅÇÞÞÅgggggÅÅgggggÅggg" << endl <<
"ÞÞÇÇÞÞÞÞüÇGÞÞÇÇÞÇÇÇ66Ïz——í—Þg6í{{——{{{{{{{{{{{{{{{—{— ›      ››››››——— ›ÞGGGGGggggGÞÞÞGgÇGGGgggggggg" << endl <<
"ÇÇ66666ü6ÇÇÇ66ÇÇ6ü6í››í—{ü6—{—{{{{—{—{{{{{{—{{{››{› › › ››  ›  ——›GÞü66gÞÅÞGÞGÞÞ6ÇÏüÇÞÞGgGggggGÇÇggg" << endl <<
"züüü6666666666ÅzÇz›››—ízÏ›——{—{{—{›——{{{{{{{{——{——› ››› ››  üzzÏüÇgÇGGÇízÇÞÞG6üÏÏ66GzzzzGÞÞÞÇGÇÇÞÞGG" << endl <<
"Ç6666666666ÇÇ›í{——›› í——›—{—{{{{{{{í{{——   ›  ››› ›› ››   ››6Þz{zíÏzÇüÇGü6ÇzÏÞGGGGÇÏÇGGÇÇÞÇ6üzízÞGGÇ" << endl <<
"6zÇÇ6ÇÇüüÏÏÏ—›í ›{—z›››—›{——{{{{›{   ›››› ›› ›  ››› ››   ››ü6ü6zíí{ííÏü6ÇÇÞÞÇzÏüÞGGGgÅÅGÅÅÞ6ÇzzzíÇÇü" << endl <<
"6Ïz6üüüüüüü{üí››— {››››——{{›     ›  ›  › ››  ›››› ››› ››››Þ6GgÇ6üüÏ66Ïü6zÇüííÏÞGGGÞÞÇGgGGgGGGGgGGGÞÅ" << endl <<
"üüüüüüüüüüüüüü— ››——› —{  › ›  › ›› ›››   ››››››››› ›—6üü6ü6üü66ü66ü66üÏÏÏÏzzÏ6ízz{Ï6{{—íÇ66ÞÞGGÞÞ6Þ" << endl <<
"üüüüí6üüüüüÏüÏí››    ›   ››› ›››››› ››››››› ›› í6üüüüüÏ666ü6ÏzÏü6ÞÇÇÇÇüÏüÏüüÏzÏzzí{{{{{{{íÏÇÇÇÏÇüÇÞz" << endl <<
"ÏzzÏzÏÏÏÏÏÏÏÏÏÏ››› ››› ››› ›››› ››››› ›› zü66üÏüüüüüüüü666üÏíÇ6üü6666üü6ü66üüü6üÏzí{ííííí{{{í6ÇÇÇzü6" << endl <<
"zÏÏÏÏÏÏÏÏÏÏÏÏüÏ í› ››››››››››› ›  ›zÏüüüüÇÇ66üüü6GÞüÏÏüüüü6üüüüüüüüÏÏüüüüüüüüÏÏÏüüÏÏüü6Ïüzzzzí{—ÏÇÇÇ" << endl <<
"ÏÏÏzÏÏÏÏÏzÏÏÏÏÏÏ››  ›› › ›› ›ÏÏÏÏÏÏüüüü66üüüüüüüüÇüÏÏÏÏÏÏÏüüüüÏÏüÏüüÏüüüÏüüüzÏÏÏüÏÏÏü666666üüü{{{{íÏ" << endl <<
"ÏÏÏÏzÏÏÏÏÏÏÏÏÏzÏÏz     ÏÏÏÏÏÏÏÏüüüüüÏÏÇüüüüüüÏüüüÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏüüÏÏÏÏüüüÏüÏÏüüÏÏÏüÏüÇGÇÇGzí{{{{" << endl <<
"ÏzzÏzzÏzÏÏzzÏÏÏzzÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏüÏÏÏ6ÇüÞüüüüÏüÏüüüü6ÏÏÏüÏüüÏüÏüÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏüüÏzÏÏ66ÇÏzÏÏííízüüÇÇ{" << endl <<
"ÏÏÏÏÏÏzÏzÏÏÏÏÏÏÏÏÏüÏÏÏÏÏzÏÏÏÏÏÏÏÏüÏü6üüüüüüü66ÏüÏüÏÏÏÏÏÏÏÏÏÏÏÏÏüÏÏzÏzzÏÏÏÏÏÏÏÏÏÏÏÏÏüÏÏÏÏzzzÏÏzzí{íüÇ" << endl <<
"zÏÏÏzÏÏÏÏÏÏÏÏzÏÏÏÏÏÏÏÏÏÏÏÏÏÏ6ÏüÏÏÏÏÏÏÏüü6üüüÏÏÏÏÏÏÏzÏÏÏzzzzzÏÏzzÏÏzÏÏÏzzÏÏÏÏÏÏÏÏÏÏÏzzÏÏÏÏÏÏÏÏÏ6Þ6ÞÞí" << endl;
    } else if (decide == 3) {
        cout <<
"                      z                                                                             " << endl <<
"                                                                                                    " << endl <<
"                                                                                                    " << endl <<
"    ü››                                                                                             " << endl <<
"        ›Ï››››                                           Æ                                          " << endl <<
"            ›{Þ—››››                               6ÇGggÆÅÆ                                         " << endl <<
"               ››—zG{››››                            g üÞ›                                          " << endl <<
"                    ›—{Ïü{—››                       {›ÞÏggÆÅüg                                      " << endl <<
"                        ››—üGz——››                  Åzíg›ÆGÞgGÆ                                     " << endl <<
"                           ›››{üGÏ{—››            › —ÅÅÅÅíÆ g6üÞ{ÞÞÅ                                " << endl <<
"                             ›››{ízÅGÏ{{››   ›  —›  ›  Çüíz›—{ Å—Æü—{Æ   G G                        " << endl <<
"                                ››—{íüGÅÞzí›Ïí—›—      Ïü6ÏÏÏÞÞÞÞggÞÇgÞÞÏÅíÆgÅíÆÆ{Æ6GÅü             " << endl <<
"                                 ››—{{íz6g—Gí{—› ›› › —gGÇÇ  ›Þg6ÅÅÞz—ÅÞÇÇÏÇÇGÇ6üüGGÇÆzgGÇ6Æ        " << endl <<
"                                  ››üzíí›í  —————›››z{{ÏGÞzí6ggÞÇÞÞÏÞÞÇÆGÅÇÆÆÏÅÆÆÆÆz6ÆÏÇ —          " << endl <<
"                                Þí›zí{›  í——›—›{ ››{ —{—üGÞüÆÅgÅÏÞÆÇü6ÏÅíÞGí{{{ÆÆí                  " << endl <<
"                            Ï›››—{{›› ›{ ›  ›            Ï{{{í6Åíz›  Ï——z——ÞzÏ                      " << endl <<
"                         —  — › ›          ›› —  —››  ›—ÞÞGgGüüÞ›ÆÆÆ G —                            " << endl <<
"                             ›{ —››{›{›—›› ›———›— ——— {ü—{6GGggÅÆGgÆü                               " << endl <<
"                                     z   ——{›  ››—— {{{—{{6üÆíÇ›Æ                                   " << endl <<
"                                                ››z›››—››››——zÅü{›                                  " << endl <<
"                                                   ›   ››   ›››—6Þ{—›                               " << endl <<
"                                                               ›››{gí—›                             " << endl <<
"                                                                  ››—Çz—›                           " << endl <<
"                                                                     ››zÏ—›                         " << endl <<
"                                                                         í6—›                       " << endl <<
"                                                                          ›—Þ—›                     " << endl <<
"                                                                            ››G—›                   " << endl <<
"                                                                              ›—g—›                 " << endl <<
"                                                                                ›—Å››               " << endl <<
"                                                                                   —Å›              " << endl <<
"                                                                                     ›6›            " << endl <<
"                                                                                        ›           " << endl;

    } else if (decide == 4) {
        cout <<
".............;. +X.X..;X:.&&;............++        :                                   .            " << endl <<
"........xX....:X$..;;:;X.;...;$$...:..+x:;+..                     :                     .    .      " << endl <<
".;.;.$;..$...............;XxXx...:x+.+.;X.:++..                .                         ..         " << endl <<
":;..;.+..................;.;;xX:..;.......X....:                                 .                  " << endl <<
"..;X:................:+.......+.X$........:::..:$                              .                    " << endl <<
".+.........x........X:.........;;;...;:......+..;.        ..                                        " << endl <<
"$..$$..;...+..+.;..:XX$:.......+...;;:..+:.x......:.                                                " << endl <<
"$$+..$:...;.X:$...;......;:.:...:..++.x......;......                           .      .             " << endl <<
".....;.:;.;+x.+.:;..X.;.:..:;;;x+X..xX&$$.xxX+...;...               :                               " << endl <<
"....;....:.X.;...........:+.:.x+   XXXX:xXxxX;.x.:... $+ .  ..X                .       .:           " << endl <<
"...::.$$..;:;....:+.;.........X:::+++XXx;:;xxx+;:++..X++:...+;$                             .       " << endl <<
"...X.....+:...;.:.;..:.;;..:.X+$XX&;;::;xx+;;;++;+xX++&;. .;: :                                     " << endl <<
"X:....:....;;:$...++::+x..x+;++xx;xXXX+XxxXxx+:;;.:;;;;:++$X+x+X.                                   " << endl <<
"X+:.:X..;;+x+xx.;.;X;X$+:::+;;:+$+:$xX+$:Xx++Xx++::;+;..:..+x+xx;;+;                                " << endl <<
"x+.:X+:;;+...;;+:$.&Xx: ..; .X .x+XX+$xX+$+:+++++Xx+x++:;;x;:+++++x;;++           .                 " << endl <<
"....;;;;;+:.;.;.&:$&+:+: &$:&:..;;...:xxxxx++;xxXX+++Xx+XX+++x;+++x;X;;+                            " << endl <<
"X;... ++;:..:;...;.&+&...$;:..... .+.. +:xxx;+x+xxxXxx+xx;;::+++x;x;+XX;+++          .              " << endl <<
"..;:....++.;+......;.:&..;X..:::......  ;:+.x;   xXxxxx:   .;;::XX+++x;+++: .+                      " << endl <<
";+;:;+;::..............::X+::.:..:..;..x::  .   :+;:. ;+x++;++::; +:+++++x+++;....                  " << endl <<
"++xx+.;;.:....:;.........:..:;..;..:.......:.:   :;;: ;;;+:;+;;:+:;; X;x;++++++x;:.                 " << endl <<
";+;..+;+:..::;...:..................;.:....X:........ ;+;$:.::   ::+;;: +:X+++x::::X:.              " << endl <<
"+.+;;;+:..::...:.:...:.....;.............XX:::....X+:    .;:;:   ::;+:: .::;;X+:::::;$X:            " << endl <<
"+;+x.+;::.:..;.::.........................+.....;.X..       :;   ::;:;: ;;:::x;$+;:x;::++           " << endl <<
";.;:.;....+:.:.........:..............x......:...+;.             . ;+:: .;;+.;.:++::::.             " << endl <<
"+;:;:;;:;+::..:.............................. ..+..                 ::  :::.;;;:::.                 " << endl <<
".:;+;;:...:.......:..................;.......+Xx..                         .;:.;.                   " << endl <<
";+;+.;.........x:....;......................+X+:;                                                   " << endl <<
";;+x::......::..........................X.;+++.                .                                    " << endl <<
";.;.:.;...:;.............................++:..                                                      " << endl <<
"..:......................................+.X      .                                                 " << endl;
    } else if (decide == 5) {

    }
}
void Game::planetArt() {
    int decide = spinner();
    if (decide == 1) {
    cout <<                                                                                                                   
    "        #                                                                                             " << endl <<
    "        ######                  .################                                                     " << endl <<
    "          #######           -########################                                                 " << endl <<
    "           ##----####     ##############################                                              " << endl <<
    "             ##- #---#####################################                                            " << endl <<
    "               -#    ---#############################-######                                          " << endl <<
    "                  #  ####--##########################----##--                                         " << endl <<
    "                   #  ######--#########################-------                                        " << endl <<
    "                  ######  #####--########################------                                       " << endl <<
    "                  #########  ####+--################------------                                      " << endl <<
    "                 #############  ####---###############----------                                      " << endl <<
    "                 ################  ####--##########--#--------                                        " << endl <<
    "            ######################## #####--#######------------                                       " << endl <<
    "           ######    #################  ####---######------. ---                                      " << endl <<
    "          # ### #    ####################  ####--##-##-----                                           " << endl <<
    "           #####     ####################--- -###---##--------                                        " << endl <<
    "            ####   #########################--  #-----##    --                                        " << endl <<
    "                 ############################----     ---##                                           " << endl <<
    "                  #######################----------      --##                                         " << endl <<
    "                   ########################----------      --#-                                       " << endl <<
    "                    ##################---####----            ---+#                                    " << endl <<
    "                     ###########---###-------  ----            ---##                                  " << endl <<
    "                      ###########------------     ---       --   ---##                                " << endl <<
    "                        ############-----   ----               ##----##-                              " << endl <<
    "                          ####------------    ---                  -#--##-                            " << endl <<
    "                             ###------------                          #--#-                           " << endl <<
    "                                  ------   -                                                          " << endl;
    } else if (decide == 2) {
    cout <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›66666üüüüÏÏÏÏz›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›666GÞÞÞÞÞÞÞÇÇÇ666zzí›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—6ÇGGGGGÞÞÞÞÞÞÞÇ66666üüíí›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—ÇÇGGGGGGGGÞÞÞÇÇÇÇÇÇ6666üüü{{›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›ÇÇgggGGGGGGÞÞÞÇÇÇÇÇÇ66666üüü{{›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›ÇÇgggggGGGÞÞÞÞÞÞÇÇÇÇÇüüüüüÏÏÏÏ———›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—ÇÇggggGGGGGGÞÞÞÞÞÇÇ6666üüüüÏÏÏÏÏ——›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—››Ç6ggggGGGGGGÞÞÞÇÇÇÇÇ666üüüüüüÏÏÏ——›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—6ggggggGGGGÞÞÞÞÞÇÇÇÇ66ÇÇ666üüüÏÏz—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—ügggggGGGGGÞÞÞÞÞÇÇÇÇ66ÇÇ666üüüÏÏÏ›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›üüggggGGGGGGÞÞÞÞÇÇÇÇ66ÇÇ666üüüÏÏ›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—ÏÏggggGGGGGÞÞÞÞÞÇÇÇÇ666üüüüüüÏÏÏ›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›ÏzgGGGGÞÞÞÞÇÇÇÇÇÇÇ6666üüüüÏÏÏÏ›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›zzGGGÞÞÞÞÇÇÇÇÇ6666üüüüÏüüÏÏÏ—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—ííÞÞÇÇÇÇÇÇÇÇ6666üüüüüÏÏÏÏz—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›í{ÇÇÇÇ6666666üüüüüÏÏÏÏ›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—{{{6666üüüüÏÏüüÏÏ—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—————————››—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›" << endl <<
    "—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—››››—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›———›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›››—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl <<
    "›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—›—" << endl;
    } else if (decide == 3) {
        cout <<
    "o               .        ___---___                    .                   " << endl <<
    "       .              .--\\        --.     .     .         ." << endl <<
    "                    ./.;_.\\     __/~ \\.     " << endl <<
    "                   /;  / `-'  __\\    . \\                " << endl <<            
    " .        .       / ,--'     / .   .;   \\        |" << endl <<
    "                 | .|       /       __   |      -O-       ." << endl <<
    "                |__/    __ |  . ;   \\ | . |      |" << endl <<
    "                |      /  \\_    . ;| \\___|    " << endl <<
    "   .    o       |      \\  .~\\___,--'     |           ." << endl <<
    "                 |     | . ; ~~~~\\_    __|" << endl <<
    "    |             \\    \\   .  .  ; \\  /_/   ." << endl <<
    "   -O-        .    \\   /         . |  ~/                  ." << endl <<
    "    |    .          ~\\ \\   .      /  /~          o" << endl <<
    "  .                   ~--___ ; ___--~       " << endl <<
    "                 .          ---         .              -JT        " << endl;
    } else if (decide == 4) {
        cout <<
"                                                      .....................:.:::::::::::::::::::::::" << endl << 
"                                                        . ........................::::::::::::::::::" << endl << 
"                                                            . .........................:.:.:::::::::" << endl << 
"                                                                 . ..............................:::" << endl << 
"                                                               .        .. ........................." << endl << 
"                                                                            . . ...................." << endl << 
"                                                                                    . .............." << endl << 
"                                               . . . . . .                                 . ......." << endl << 
"                                            .  . ..... . .                                          " << endl << 
"                                          . .............. .  =                                     " << endl << 
"                                        . . ...%@@@@%......#:   %                                   " << endl <<
"                                        . ..@@@@@@@@@@@@@..=-@@                                     " << endl << 
"                                      . . =@@@@@@@@@@@@@@=. .*%                                     " << endl << 
"                                       . .@@@@@@@@@@@@@@@@:@* :                                     " << endl << 
"                                       . @@@@@@@@@@@@@@@@@@..==.                                    " << endl << 
"                                       . @@@@@@@@@@@@@@@@@@. .                                      " << endl << 
"                                       *@:@@@@@@@@@@@@@@@@. .                                       " << endl <<
"                                     -@ - -@@@@@%@@@@@@@@=. .                                       " << endl << 
"                                   % @ -= =@%@@@@@@@@@@@. .                                         " << endl << 
"                                  .%   #-  .%% *@@@@*. . .                                          " << endl << 
"                                           #%% . . . .                                              " << endl << 
"                                                                                                    " << endl << 
"                                                                                                    " << endl << 
"                                                                                                    " << endl;
    } else {
        cout <<
"                          ....:::;;;;;+::::.                  .:XXXXxxx++++++;;;;;::;::;:::;++:::::&" << endl << 
" ;                        ...::;;;;;++++:::.                  .:XXxxx++++++;;++x:::;:;:::::+x::::&&:" << endl << 
"                          .;.:;;;;+++++:::.                  ..:xxxxxx+++;;;;;:;:;::::;:::::::::&&::" << endl << 
"                           ..:::++++++::::.                  ..:xxxxXX+;;;;;::::;:;:;:::::::::&&::::" << endl << 
"                            ...:::::::::.                    ..:xxXXX+;;;;:;:;;:::::::::::::&&::::::" << endl << 
"                              ....::...                       .:+++;;;;;:;::;:::;:::::::;;&&::::::::" << endl << 
"                                                              .:++;;;;::;:;:::;::::::::;&&++::::::::" << endl << 
"                        :                                     .::;;;;::;::;::::::::::;&&+++x::::::::" << endl << 
"                                                  ;$:          .:;;::;::;:::::::::::&&:++x::::::::::" << endl << 
"          .:;++x;:   .. .. ... .                                .:X::;:::;:::;+x::&&::::::::::::::::" << endl << 
"        .++++xxxXXX;.. ......... .. ..    ;                     ..::;::;::::::::&&::::::::::::::::::" << endl << 
"       :++++xxXXXXXX;..::::::::......  ..                    .   ..:::::::::::&&::::::::::::::::::::" << endl << 
"       ;++xxXXXXXX$$$$;:::::::::::::....  .                .       .:::::::&&&::::::::::::::::::::;;" << endl << 
"       ;xxXXXXX$$$$x:............::::::... ..             .         ..:::&&::::::::::::::::;;:::::::" << endl << 
"       .XXXXX$$$;.:........:.......::::::...  .          .            XXX:::::::::::::::::::::::::;;" << endl << 
"     .  .;X$$$:.:::&&.::.:::.:.......::::::... .        .:         xxX  ..::::::::::::::::::::::;;;;" << endl << 
"   :. ....:::..:.&&.:::::::::::::..:..::::::..  .       :       X$x        ..:::::::::::::::::;;;;;:" << endl << 
"      ...:::......:::::::::::::::::.:..::::::..  .      :; ;++++:::            ...:::::::::::::::..." << endl << 
"    ....:::....&:.:::::::::::::::.::...:::::::..   .                              :  ........       " << endl << 
"   .  ..::....::::::::::::::::::::::.:..::::::... .                             X                   " << endl << 
"   . ...::...:XX$$$$$$$$::::::::$XXXXXXXXX:::::..                                                   " << endl << 
"    ...:::.++x+xxxxxXXXXXXX:;xxxxxxxxxxxxxxX:::...  .                                        X:     " << endl << 
"  .  ..:::+++++++++++++++++++++++++++++++$$$:::.. .                                                 " << endl << 
"   . ...::;;;;;;;;;;;;;;+++++++++;;;;++xXXXX::... .       :                                         " << endl << 
"   .  ..:::;;;;;;;$$+;;;;;;;;;;;;;;+++++xxXX::..                           ..:::.                   " << endl << 
"    .. ..::;xxxxXXXXXXXXX$;;;;;;;;;;;+++xxX++;;;;.                        ::;+++::.                 " << endl << 
"      ...:::+++++++++++++xxxx;;;;;;;+++$&&+++;;;;  .                     .::++xXX:.                 " << endl << 
"   .  . ..:::.;;;;;;;;;;;;+++++++xXXXX$$$::+;;;;;                        .::xXXX:::             .   " << endl << 
"       . ...:::::::::;;;;;;;;++++xxXX$$:::....   .                         .:::::.            $     " << endl << 
"     .   . ...::::::::::;;;;;+++xXXX$:::....  .                                   :;                " << endl;
        }
}