#include"../headers/player.h"

/* Bottom Line Up Front:
The Player class will contain the player's number, advisor, location and statistics.

The primary function used by the Player stat will be the menu (for now - if I add a combat system,
that nmight change).

Outside of that, the player is basically a slightly more important struct to me right now. I promise, I will 
add more - I might allow players to set their own Player character within certian parameters, we'll see.
*/

Player::Player() {
    _playerNum = 0;
    _strength = 0;
    _age = 0;
    _wisdom = 0;
    _stamina = 0;
    _location = 0;

}

Player::Player(int num, int age, int stam, int str, int wis, int pride) {
    _playerNum = num;
    _age = age;
    _stamina = stam;
    _strength = str;
    _wisdom = wis;
    _pride = pride;
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
int Player::getStamina() { return _stamina; }
int Player::getStrength() { return _strength; }
int Player::getWisdom() { return _wisdom; }
int Player::getPride() { return _pride; }
int Player::getLocation() { return _location; }
int Player::getPlayerNum() {return _playerNum; }
Advisor Player::getPlayerAdvisor() { return playerAdvisor; }

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
