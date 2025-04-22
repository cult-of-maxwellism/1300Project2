#pragma once

#include"advisors.h"
#include"characters.h"

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
    int getPoints();
    int getLocation();
    int getPlayerNum();
    Advisor getPlayerAdvisor();

    //setters
    void setAdvisor(Advisor chosen);
    void changeStamina (int newStam);
    void changeStrength (int newStr);
    void changeWisdom(int newWis);
    void changePoints(int newPoints);

    //technically a setter, move function
    void move (int movement);

    private:
    int inputChecker(std::string); //internal function to ensure string is just numbers
    int _playerNum;
    int _age;
    int _stamina;
    int _strength;
    int _wisdom;
    int _points;
    int _location;

    Advisor playerAdvisor;
    std::string playerName;
};
