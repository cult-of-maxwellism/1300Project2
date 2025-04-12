#include"../headers/libraries.h"
#include"../headers/game.h"
#include"../headers/player.h"
#include"../headers/Board.h"

//constructors
void Game () {
    //need to figure out what goes in the default constructor
    //player
    //board
    //events
    //advisors
    //characters
    //riddles
}

void Game (int playerNumber, string eventsFile, string advisorFile, string characterFile, string riddleFile) {
    //all of these beautiful things, declared!
}

//Functions
void Game::gameMasterInit () {
    advisorPuller("../input_files/advisors.txt");
    characterPuller("../input_files/characters.txt");
    // this will split all the text files into the vectors used from here on out
    // additionally, it'll display the character array
    // Finally, it will ask players to select a character and a path.
}

int Game::gameMaster (int player) {
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
    string filename = "";
    cout << "Tell me the name of your save file." << endl;
    cin >> filename;
}