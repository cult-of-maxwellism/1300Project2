#pragma once
#include<string>
#include<vector>
#include"advisors.h"
#include"characters.h"

class Player {
    public:
    //constructor
    Player();
    Player(int num, int age, int stam, int str, int wis, int points, int board);
    //function
    void menu();
    //getter
    int getStamina();
    int getStrength();
    int getWisdom();
    int getPoints();
    int getLocation();
    int getPlayerNum();
    int getBoardType();
    int gameOver();
    std::string getPlayerName();
    std::string getCharName();
    Advisor getPlayerAdvisor();

    //setters
    void setAdvisor(Advisor chosen);
    void changeStamina (int newStam);
    void changeStrength (int newStr);
    void changeWisdom(int newWis);
    void changePoints(int newPoints);
    void setLocation (int location);

    //technically a setter, move function
    void move (int movement);

    private:
    int inputChecker(std::string); //internal function to ensure string is just numbers

    //variables for the player class
    int _playerNum;
    int _age;
    int _stamina;
    int _strength;
    int _wisdom;
    int _points;
    int _location;
    int _boardType;
    std::string charName;

    void pointConvert();

    //and here's the little things each player holds.
    Advisor _playerAdvisor;
    std::string _playerName;
    Characters _player_character;
};
