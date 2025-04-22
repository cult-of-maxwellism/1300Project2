/*
#pragma once
//this essentially replaces the old "guard" ifndef & define statements.
// This ensures these definitions are only included once on compile, and
// prevents errors coming from the compiler trying to figure out why I keep
// redefining everything.

#include"libraries.h"

#include <memory>
#include<string>
using namespace std;

struct Advisor {
    string name, ability, abilityDesc;
};

struct Characters {
    string name;
    int age, stamina, strength, wisdom, points;
};

struct Events {
    string event;
    int path, advisor, points; 
};

struct Riddles {
    string riddle, type, answer;
};

int spinner ();

class Menu {
    public:
    Menu();
    Menu(int);
    private: 
    string inputChecker(string);
};
*/
