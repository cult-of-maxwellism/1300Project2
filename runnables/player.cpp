#include<iostream>
#include <ostream>

#include"../headers/player.h"
#include"../headers/input_san.h"

/* Bottom Line Up Front:
The Player class will contain the player's number, advisor, location and statistics.

The primary function used by the Player stat will be the menu. Outside of that, the player is basically a slightly more important struct to me.

I might allow players to set their own Player character within certian parameters, we'll see.
*/

using namespace std;

//constructors
Player::Player() {
    _playerNum = 0;
    _strength = 0;
    _age = 0;
    _wisdom = 0;
    _stamina = 0;
    _location = 0;
    _boardType = 0;
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
}

//interactive function - menu
void Player::menu () {
    int userInput=0, chooser = 0;

    while (userInput != 5) {
        cout << _playerName << "'s Menu: Select an option to continue..." << endl
            << "1. Check Player Progress (1)" << endl
            << "2. Review Character (2)" << endl
            << "3. Check Position (3)" << endl
            << "4. Review your Advisor (4)" << endl
            << "5. Move Forward (5)" << endl << endl
            << "Please choose an option using the corresponding number:" << endl;

        //I sanatize input here
        userInput = input_san();

        switch (userInput) {
            case 1:
            pointConvert();
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
                 << "Description: " << _playerAdvisor.abilityDesc << endl
                 << "Do you want to fire your advisor, making them unable to work for any player for the rest of the game (1 for yes, 2 for no)?" << endl;
                while (chooser != 1 && chooser != 2) {
                    chooser = input_san();
                }
                if (chooser == 1) {
                    Advisor blankAdvisor;
                    _playerAdvisor = blankAdvisor;
                } else {
                    cout << "Probably smart: they tend to both have families and superpowers." << endl;
                }
            break;

            case 5:
            cout << "Moving!" << endl;
            break;

            default:
            cout << "User input not recognized, please choose from the menu!" << endl;

        }
    }
}

//getters
int Player::getStamina() { return _stamina; }
int Player::getStrength() { return _strength; }
int Player::getWisdom() { return _wisdom; }
int Player::getPoints() { return _points; }
int Player::getLocation() { return _location; }
int Player::getPlayerNum() {return _playerNum; }
int Player::getBoardType() { return _boardType; }
Advisor Player::getPlayerAdvisor() { return _playerAdvisor; }
string Player::getPlayerName() { return _playerName; }

//setters
void Player::setLocation(int location) { _location = location; }
void Player::setAdvisor(Advisor chosen) {
    _playerAdvisor = chosen;
}

//changers
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

//point calculation: convert
void Player::pointConvert() {
    int userIn = 0, userChooser = 0, points = -1;
    cout << "Player " << _playerName << " progress:" << endl
            << "1. Stamina (HEALTH): " << _stamina << endl
            << "2. Strength  (ATK) : " << _strength << endl
            << "3. Wisdom    (DEF) : " << _wisdom << endl
            << "4. Points    (PTS) : " << _points << endl << "Do you wish to do any conversions?" << endl;
    while (userIn <= 0 || userIn > 5) {
        cout << "Select 1 through 4 to convert that stat, and 5 to continue without converting." << endl;
        userIn = input_san();

        //actual menu logic
        if (userIn == 1) {
            //stamina chooser
            while (userChooser < 0 || userChooser > 3) {
                cout << "What do you want to change your stamina to (1 for STR, 2 for WIS, 3 for pts)" << endl;
                userChooser = input_san();
                if (userChooser < 0 || userChooser > 3) {
                    cout << "incorrect input!" << endl;
                }
            }
            while (points > _stamina || points < 0) {
                cout << "Input points you wish to exchange!" << endl;
                points = input_san();
            }
            if (userChooser == 1) {
                changeStrength(points);
                changeStamina(-points);
            } else if (userChooser == 2) {
                changeWisdom(points);
                changeStamina(-points);
            } else if (userChooser == 3) {
                changePoints(points*10);
                changeStamina(-points);
            }
        } else if (userIn == 2) {
            //strength chooser
            while (userChooser < 0 || userChooser > 3) {
                cout << "What do you want to change your strength to (1 for STA, 2 for WIS, 3 for pts)" << endl;
                userChooser = input_san();
                if (userChooser < 0 || userChooser > 3) {
                    cout << "incorrect input!" << endl;
                }
            }
            while (points > _strength || points < 0) {
                cout << "Input points you wish to exchange!" << endl;
                points = input_san();
            }
            if (userChooser == 1) {
                changeStamina(points);
                changeStrength(-points);
            } else if (userChooser == 2) {
                changeWisdom(points);
                changeStrength(-points);
            } else if (userChooser == 3) {
                changePoints(points*10);
                changeStrength(-points);
            }
        } else if (userIn == 3) {
            //wisdom chooser
            while (userChooser < 0 || userChooser > 3) {
                cout << "What do you want to change your wisdom to (1 for STR, 2 for STA, 3 for pts)" << endl;
                userChooser = input_san();
                if (userChooser < 0 || userChooser > 3) {
                    cout << "incorrect input!" << endl;
                }
            }
            while (points > _wisdom || points < 0) {
                cout << "Input points you wish to exchange!" << endl;
                points = input_san();
            }
            if (userChooser == 1) {
                changeStrength(points);
                changeWisdom(-points);
            } else if (userChooser == 2) {
                changeStamina(points);
                changeWisdom(-points);
            } else if (userChooser == 3) {
                changePoints(points*10);
                changeWisdom(-points);
            }
        } else if (userIn == 4) {
            //points chooser
            while (userChooser < 0 || userChooser > 3) {
                cout << "What do you want to change your wisdom to (1 for STR, 2 for STA, 3 for WIS)" << endl
                     << "Remember, PTS are worth 10x the units of STR/STA/WIS!" << endl;
                userChooser = input_san();
                if (userChooser < 0 || userChooser > 3) {
                    cout << "incorrect input!" << endl;
                }
            }
            while (points > _points || points < 0) {
                cout << "Input points you wish to exchange!" << endl;
                points = input_san();
            }
            if (userChooser == 1) {
                changeStrength((points/10));
                changePoints(-points);
            } else if (userChooser == 2) {
                changeStamina((points/10));
                changePoints(-points);
            } else if (userChooser == 3) {
                changeWisdom((points/10));
                changePoints(-points);
            }
        } else {
            cout << "Invalid option!" << endl;
        }
    }
}
//point calculation: final
int Player::gameOver() {
    int totalPoints = _points;
    totalPoints += (_wisdom*10);
    totalPoints += (_strength*10);
    totalPoints += (_stamina*10);
    return totalPoints;
}