//#include"../headers/libraries.h"
#include"../headers/game.h"
#include"../headers/player.h"
#include"../headers/Board.h"

void Game () {
    //need to figure out what goes in the default constructor
    //player
    //board
    //events
    //advisors
    //characters
    //riddles
}

void Game (Player players[], Board gameBoard, string eventsFile, string advisorFile, string characterFile, string riddleFile) {

}

void Game::gameMaster () {
    string filename = "";
    cout << "Tell me the name of your save file." << endl;
    cin >> filename;
    advisorPuller("../input_files/advisors.txt");
    characterPuller("../input_files/characters.txt");
}


void Game::advisorPuller(string filename) {
    //this will pull in a file and feed the vector advisors with advisors.
}
void Game::characterPuller(string filename) {
    //this will pull in a file and feed the vector characters with characters from the file
}
void Game::characterSelect() {
    //menu that'll get called at the start for choosing characters from the vector.
}
void Game::advisorSelect() {
    //menu that'll get called for choosing advisors, whenever that tile gets hit.
}

void Game::saveGame() {
    //this, when called, will print current game state to a text file
}

void Game::loadGame(string savedGame) {
    //this will take a given savegame, add .txt to it, find it, and load it.
}