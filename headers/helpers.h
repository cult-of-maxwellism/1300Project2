#include"libraries.h"

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
