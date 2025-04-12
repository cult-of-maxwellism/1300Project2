#pragma once
//this essentially replaces the old "guard" ifndef & define statements.
// This ensures these definitions are only included once on compile, and
// prevents errors coming from the compiler trying to figure out why I keep
// redefining everything.

#include"libraries.h"
#include"helpers.h"

class Game {
    public:
    //game function
    int gameMaster (int player);
    void gameMasterInit ();

    //constructor
    Game();
    Game(int playerNumber, string eventsFile, string advisorFile, string characterFile, string riddleFile);

    private:
    //functions
    void advisorPuller(string filename);
    void characterPuller(string filename);
    void characterSelect();
    void advisorSelect();
    void saveGame();
    void loadGame(string savedGame);

    //variables
    vector<Characters> characters;
    vector<Advisor> advisors;
};