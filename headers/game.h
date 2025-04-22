#pragma once

#include<string>
#include<vector>

#include"advisors.h"
#include"characters.h"
#include"events.h"
#include"player.h"
#include"riddles.h"

class Game {
    public:
    //constructor
    Game();
    Game(int playerNumber, std::string eventsFile, std::string advisorFile, std::string characterFile, std::string riddleFile);

    //game function
    void gameMaster ();
    void gameMasterInit ();
    //turn function, incredibly important
    int turn(int player);

    private:
    //vector builders for each struct
    void advisorPuller(std::string filename);
    void characterPuller(std::string filename);
    void eventPuller(std::string filename);
    void riddlePuller(std::string filename);

    //Selector and menu functions
    void characterSelect();
    void advisorSelect();
    void mainMenu();
    void gameOver();
    void highScore();

    //save, load, combat, and other stretch goals
    void saveGame();
    void loadGame(std::string savedGame);
    void combat(int player, int scenario);

    //variables
    std::vector<Characters> _characters;
    std::vector<Advisor> _advisors;
    std::vector<Events> _events;
    std::vector<Riddles> _riddles;
    std::vector<Player> _players;
};