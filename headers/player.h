#include"libraries.h"
//#include"helpers.h"
#include"../headers/libraries.h"

class Player {
    public:
    Player();
    Player(int);
    void menu();
    private:
    string inputChecker(string);
    int age, stamina, strength, wisdom, pride;
    //Advisor playerAdvisor;
    string playerName;
};