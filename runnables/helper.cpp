#include"../headers/libraries.h"

//useless .cpp file for now, I plan on including misc functions as I add functionality here.

void sortMe () {}

int spinner () {
    int result = rand()%6;
    cout << "This dice has landed on: " << result+1 << endl;
    return result+1;
}

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

//int spinner ();