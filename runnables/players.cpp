#include"../headers/player.h"

void Player::menu () {
    int userInput=0;

    while (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput !=5) {
        cout << "Main Menu: Select an option to continue..." << endl
            << "1. Check Player Progress (1)" << endl
            << "2. Review Character (2)" << endl
            << "3. Check Position (3)" << endl
            << "4. Review your Advisor (4)" << endl
            << "5. Move Forward (5)" << endl << endl
            << "Please choose an option using the corresponding number:" << endl;

        cin >> userInput;

        switch (userInput) {
            case 1:
            
            break;
            case 2:
            cout << "Player " << playerName << " progress:" << endl
            << "Age:      " << age << endl
            << "Stamina:  " << stamina << endl
            << "Strength: " << strength << endl
            << "Wisdom:   " << wisdom << endl
            << "Pride:    " << pride << endl;

            break;
            case 3:

            break;
            case 4:

            break;

            case 5:
            //this will interact with board from player to
            break;
            default:
            cout << "User input not recognized, please take from the menu!" << endl;

        }
    }
}

string Player::inputChecker (string) {
    return "jhaha";
}