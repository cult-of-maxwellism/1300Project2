#pragma once
//this essentially replaces the old "guard" ifndef & define statements.
// This ensures these definitions are only included once on compile, and
// prevents errors coming from the compiler trying to figure out why I keep
// redefining everything.

#include"libraries.h"

#include<string>
using namespace std;

struct Advisor {
    string name, abilityText;
    int ability;
};

struct Characters {
    string name;
    int age, stamina, strength, wisdom, pride;
};

struct Events {
    string event;
    int path, advisor, points; 
};

struct Riddles {
    string riddle, type, answer;
};
/*
class Menu {
    public:
    Menu();
    Menu(int);
    private: 
    string inputChecker(string);
};
*/
