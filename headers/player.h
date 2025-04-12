#pragma once
//this essentially replaces the old "guard" ifndef & define statements.
// This ensures these definitions are only included once on compile, and
// prevents errors coming from the compiler trying to figure out why I keep
// redefining everything.

#include"libraries.h"
#include"helpers.h"

/* Bottom Line Up Front:
The Player class will contain the player's number, advisor, location and statistics.

The primary function used by the Player stat will be the menu (for now - if I add a combat system,
that nmight change).

Outside of that, the player is basically a slightly more important struct to me right now. I promise, I will 
add more - I might allow players to set their own Player character within certian parameters, we'll see.
*/

class Player {
    public:
    //constructor
    Player();
    Player(int num, int age, int stam, int str, int wis, int pride);
    //function
    void menu();
    //getter
    int getStamina();
    int getStrength();
    int getWisdom();
    int getPride();
    int getLocation();
    int getPlayerNum();
    Advisor getPlayerAdvisor();

    //setters
    void setAdvisor(Advisor chosen);
    void changeStamina (int newStam);
    void changeStrength (int newStr);
    void changeWisdom(int newWis);
    void changePride(int newPride);

    //technically a setter
    void move (int movement);

    private:
    int inputChecker(string); //internal function to ensure string is just numbers
    int _playerNum;
    int _age;
    int _stamina;
    int _strength;
    int _wisdom;
    int _pride;
    int _location;

    Advisor playerAdvisor;
    string playerName;
};
