#include"../headers/player.h"

void Player() {

}

void Player(int num) {

}

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
            << "Age:      " << _age << endl
            << "Stamina:  " << _stamina << endl
            << "Strength: " << _strength << endl
            << "Wisdom:   " << _wisdom << endl
            << "Pride:    " << _pride << endl;

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

//getter
int Player::getStamina() {
    return _stamina;
}
int Player::getStrength() {
    return _strength;
}
int Player::getWisdom() {
    return _wisdom;
}
int Player::getPride() {
    return _pride;
}
int Player::getLocation() {
    return _location;
}

void Player::setAdvisor(Advisor chosen) {
    //this is gonna do a little compare to make sure it won't just put a blank advisor in, then it'll set advisor.
}

void Player::changeStamina (int newStam) {
    if (newStam >= 0) {
        _stamina = newStam;
    }
}
void Player::changeStrength (int newStr) {
    if (newStr >= 0) {
        _strength = newStr;
    }
}
void Player::changeWisdom(int newWis) {
    if (newWis >= 0) {
        _wisdom = newWis;
    }
}
void Player::changePride(int newPride) {
    if (newPride >= 0) {
        _pride = newPride;
    }
}
void Player::move (int movement) {
    //complicated move stuff
}


int Player::inputChecker (string) {
    return 2;
}
