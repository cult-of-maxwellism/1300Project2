#include<iostream>
#include <ostream>
#include <utility>

#include"../headers/player.h"

/* Bottom Line Up Front:
The Player class will contain the player's number, advisor, location and statistics.

The primary function used by the Player stat will be the menu (for now - if I add a combat system,
that nmight change).

Outside of that, the player is basically a slightly more important struct to me right now. I promise, I will 
add more - I might allow players to set their own Player character within certian parameters, we'll see.
*/

using namespace std;

Player::Player() {
    _playerNum = 0;
    _strength = 0;
    _age = 0;
    _wisdom = 0;
    _stamina = 0;
    _location = 0;

}

Player::Player(int num, int age, int stam, int str, int wis, int points, int board) {
    _playerNum = num;
    _age = age;
    _stamina = stam;
    _strength = str;
    _wisdom = wis;
    _points = points;
    _location = 0;
    _boardType = board;

    string userName;

    cout << "What's your name, player?" << endl;
    cin >> userName;

    _playerName = userName;
    /*
    cout << "Choose your character!" << endl;
    for (int i = 0; i < avalibleChars.size(); i++) {
        cout<< avalibleChars[i].name << ", age " << avalibleChars[i].age << endl
            << "Strength: " << avalibleChars[i].strength << " Stamina: "
            << avalibleChars[i].stamina << " Wisdom: " << avalibleChars[i].wisdom << endl;
    }
            */
}

void Player::menu () {
    int userInput=0, userIn = 0, points = 0;

    while (userInput != 5) {
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
            cout << "Player " << _playerName << " progress:" << endl
                 << "1. Stamina:  " << _stamina << endl
                 << "2. Strength: " << _strength << endl
                 << "3. Wisdom:   " << _wisdom << endl
                 << "Points:   " << _points << endl << "Do you wish to convert any of the above to points (at a ratio of 100 to 1000 points)?" << endl;
            while (userIn <= 0 || userIn > 4) {
                cout << "Select 1 through 3 to convert, and 4 to continue without converting." << endl;
                cin >> userIn;
                if (userIn == 1) {
                    cout << "Enter the number of Stamina points you'd like to sacrifice." << endl;
                    cin >> points;
                    if (points < _stamina) {
                        points = -_stamina;
                    }
                    if (points > 0) {
                        points = points*(-1);
                    }
                    changeStamina(points);
                    points = points*-10;
                    changePoints(points);
                } else if (userIn == 2) {
                    cout << "Enter the number of Strength points you'd like to sacrifice." << endl;
                    cin >> points;
                    if (points > _strength) {
                        points = -_strength;
                    }
                    if (points > 0) {
                        points = points*(-1);
                    }
                    changeStrength(points);
                    points = points*-10;
                    changePoints(points);
                } else if (userIn == 3) {
                    cout << "Enter the number of Wisdom points you'd like to sacrifice." << endl;
                    cin >> points;
                    if (points > _wisdom) {
                        points = -_wisdom;
                    }
                    if (points > 0) {
                        points = points*(-1);
                    }
                    changeWisdom(points);
                    points = points*-10;
                    changePoints(points);
                } else if (userIn == 4) {
                    break;
                } else {
                    cout << "Invalid option!" << endl;
                }
            }
            break;

            case 2:
            cout << "Player " << _playerName << " character stats:" << endl
            << "Age:      " << _age << endl
            << "Stamina:  " << _stamina << endl
            << "Strength: " << _strength << endl
            << "Wisdom:   " << _wisdom << endl
            << "Points:   " << _points << endl;
            break;

            case 3:
            cout << "Player " << _playerName << " location: " << _location << endl;
            break;
            case 4:
            cout << "Player " << _playerName << "'s advisor is " << _playerAdvisor.name << endl
                 << "Ability: " << _playerAdvisor.ability << endl
                 << "Description: " << _playerAdvisor.abilityDesc << endl;
            break;

            case 5:
            cout << "Moving!" << endl;
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
int Player::getPoints() { return _points; }
int Player::getLocation() { return _location; }
int Player::getPlayerNum() {return _playerNum; }
int Player::getBoardType() { return _boardType; }
Advisor Player::getPlayerAdvisor() { return _playerAdvisor; }
string Player::getPlayerName() { return _playerName; }

void Player::setAdvisor(Advisor chosen) {
    //this is gonna do a little compare to make sure it won't just put a blank advisor in, then it'll set advisor.
}

void Player::changeStamina (int stamChange) {
    int newStam = _strength+stamChange;
    if (newStam < 100) {
        _stamina = 100;
    } else {
        _stamina = newStam;
    }
}
void Player::changeStrength (int strChange) {
    int newStr = _strength+strChange;
    if (newStr < 100) {
        _strength = 100;
    } else {
        _strength = newStr;
    }
}
void Player::changeWisdom(int wisChange) {
    int newWis = _wisdom+wisChange;
    if (newWis < 100) {
        _wisdom = 100;
    } else {
        _wisdom = newWis;
    }
}
void Player::changePoints(int pointsChange) {
    _points+=pointsChange;
}

void Player::move (int movement) {
    _location += movement;    
}


int Player::inputChecker (string) {
    return 2;
}
