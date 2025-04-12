#pragma once
//this essentially replaces the old "guard" ifndef & define statements.
// This ensures these definitions are only included once on compile, and
// prevents errors coming from the compiler trying to figure out why I keep
// redefining everything.

#include"libraries.h"
#include"helpers.h"

class Player {
    public:
    //constructor
    Player();
    Player(int);
    //function
    void menu();
    //getter
    int getStamina();
    int getStrength();
    int getWisdom();
    int getPride();
    int getLocation();

    void setAdvisor(Advisor chosen);
    //I should probably make additional functions that change stats
    void changeStamina (int newStam);
    void changeStrength (int newStr);
    void changeWisdom(int newWis);
    void changePride(int newPride);
    void move (int movement);

    private:
    int inputChecker(string); //internal function to ensure string is just numbers
    int _age;
    int _stamina;
    int _strength;
    int _wisdom;
    int _pride;
    int _location;

    Advisor playerAdvisor;
    string playerName;
};
