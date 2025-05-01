#include"../headers/Board.h"
#include"../headers/board-player.h"
#include<ostream>
#include<stdlib.h>
#include<iostream>
#include<vector>

#define RED "\033[48;2;230;10;10m" // R, hyena
#define GREEN "\033[48;2;34;139;34m" // G, grassland /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m" // B, oasis
#define PINK "\033[48;2;255;105;180m" // P, advisor
#define BROWN "\033[48;2;139;69;19m" // N, hyena
#define PURPLE "\033[48;2;128;0;128m" // U, challenge
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0), end */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128), start */
#define RESET "\033[0m"

//Tile type chars are: O (last block), Y (first block), G (grasslands), P (advisor), U (challenge), R (graveyard), N (hyena), B (oasis)
using namespace std;

//init board
void Board::initializeBoard(){
    //cout << "Players size at init board " << _board_players.size() << endl;
    for (int i = 0; i < 2; i++) {
        if (i==0) {
            initializeTiles(i, i); //Ensures unique distribution
          } else {
            initializeTiles(i, i);
          }
    }
}

//creates each tile
void Board::initializeTiles(int player_index, int boardType) {
    //cout << "Players size at init tiles " << _board_players.size() << endl;
    Tile temp;
    int green_count = 0, special_tiles = 0;
    int total_tiles = _BOARD_SIZE, tileType;

    if (boardType == 0) { // Normal Difficulty
        for (int i = 0; i < total_tiles; i++) {
            tileType=rand()%20;
            if (i == total_tiles - 1) {
                temp.color = 'O'; //last block orange
            } else if (i == 0) {
                temp.color = 'Y'; //starting block grey
            } else {
                if (green_count < 20 && rand() % (total_tiles-i) < 20 - green_count) {
                    temp.color = 'G'; //grasslands
                    green_count++;
                } else if (tileType <= 4 && special_tiles < 30) {
                    temp.color = 'P'; // advisors will be pink
                    special_tiles++;
                } else if (tileType >= 10 && tileType <= 15 && special_tiles < 30) {
                    temp.color = 'U'; // purple for challenge tile
                    special_tiles++;
                } else if (i <= (total_tiles/2) && special_tiles < 30) {
                    tileType=rand()%20;
                    if (tileType >= 0 && tileType <= 10 && _tiles[player_index][i-1].color != 'R') {
                        temp.color = 'R'; //red, for graveyards
                        special_tiles++;
                    } else if (tileType > 10 && tileType <= 15) {
                        temp.color = 'N'; //brown, for hyenas
                        special_tiles++;
                    } else if ((tileType) == 18) {
                        temp.color = 'B'; //blue for oasis
                        special_tiles++;
                    }
                } else if (i > (total_tiles/2) && special_tiles < 30) {
                    tileType=rand()%20;
                    if (tileType >= 0 && tileType <= 3) {
                        temp.color = 'R'; //red, for graveyards
                        special_tiles++;
                        //graveyard++;
                    } else if (tileType > 4 && tileType <= 7) {
                        temp.color = 'N'; //brown, for hyenas
                        special_tiles++;
                        //hyena++;
                    } else if (tileType >= 10 && tileType <= 20) {
                        temp.color = 'B'; //blue for oasis
                        special_tiles++;
                        //oasis++;
                    }
                } else if (green_count < 20) {
                    temp.color = 'G';
                    green_count++;
                }
            }
            _tiles[player_index][i] = temp;
        }
    } else if (boardType == 1) { // cub training 
        for (int i = 0; i < total_tiles; i++) {
            tileType=rand()%20;
            if (i == total_tiles - 1) {
                temp.color = 'O'; //last block orange
            } else if (i == 0) {
                temp.color = 'Y'; //starting block grey
            } else if (green_count < 30 && rand() % (total_tiles-i) < 30 - green_count) {
                temp.color = 'G'; //grasslands
                green_count++;
            } else if (tileType <= 4 && special_tiles < 20) { //20% chance
                temp.color = 'N'; //brown, for hyenas
                special_tiles++;
            } else if (tileType >= 10 && tileType <= 14 && _tiles[player_index][i-1].color != 'R') { //20% chance, unless the last tile was also one of these
                temp.color = 'R'; //red, for graveyards
                special_tiles++;
            } else if (tileType >= 15 && tileType <= 18) { //15% chance
                temp.color = 'P'; // advisors will be pink
                    special_tiles++;
            } else if (i <= (total_tiles/2) && special_tiles < 20) { //first half of the board
                tileType=rand()%20;
                if (tileType >= 0 && tileType <= 5) { //25% chance
                    temp.color = 'B'; //blue for oasis
                    special_tiles++;
                } else if (tileType >= 10 && tileType <= 14) { //15% chance
                    temp.color = 'U'; // red for challenge tile
                    special_tiles++;
                }
            } else if (i > (total_tiles/2) && special_tiles < 20) { //second half of the board
                tileType=rand()%20;
                if (tileType >= 0 && tileType <= 3) { //15% chance
                    temp.color = 'B'; //blue for oasis
                    special_tiles++;
                } else if (tileType > 4 && tileType <= 10) { //30% chance
                    temp.color = 'U'; //purple for challenge tile
                    special_tiles++;
                }
            } else if (green_count < 30) {
                temp.color = 'G';
                green_count++;
            }
            _tiles[player_index][i] = temp;
        }
    }
}

Board::Board() {
    //default is for testing, mostly
    _player_count = 2;
    // Initialize board
    initializeBoard();
}

//constructor
Board::Board (vector<Player> players){
    _player_count = players.size();
    board_player temp;
    // Initialize player position
    for (int i = 0; i < _player_count; i++) {
        temp.position = players.at(i).getLocation();
        temp.board_type = players.at(i).getBoardType();

        _board_players.push_back(temp);
    }

    //cout << "Players size at Board::Board " << _board_players.size() << endl;
    // Initialize tiles
    initializeBoard();
}

void Board::displayTile(int board_type, int pos, vector<board_player> players) {
    //cout << "Players size at beginning of displayTile " << players.size() << endl;
    // string space = "                                       ";
    string color = "";

    // Template for displaying a tile: <line filler space> <color start>
    // |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[board_type][pos].color == 'R') {
        color = RED;
    } else if (_tiles[board_type][pos].color == 'G') {
        color = GREEN;
    } else if (_tiles[board_type][pos].color == 'B') {
        color = BLUE;
    } else if (_tiles[board_type][pos].color == 'U') {
        color = PURPLE;
    } else if (_tiles[board_type][pos].color == 'N') {
        color = BROWN;
    } else if (_tiles[board_type][pos].color == 'P') {
        color = PINK;
    } else if (_tiles[board_type][pos].color == 'O') {
        color = ORANGE;
    } else if (_tiles[board_type][pos].color == 'Y') {
        color = GREY;
    } else {
        color = GREEN; //default to green if no color or weird color.
    }

    //cout << "players size at draw tiles: " << players.size() << endl;
    cout << color << "|";

    bool any = false;
    for (int i = 0; i < _player_count; ++i) {
        if (players[i].board_type == board_type && players[i].position == pos) {
            if (any) cout << " & ";
            cout << i + 1;
            any = true;
        }
    }

    if (!any) {
        cout << "  ";
    }

    cout << "|" << RESET;
}

void Board::displayTrack(int board_type, vector<board_player> players) {
    //cout << "Players size at displayTrack " << players.size() << endl;
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(board_type, i, players);
    }
}

void Board::displayBoard() {
    //cout << "Players size at display board: " << _board_players.size() << endl;
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            cout << endl << "Normal Difficulty:" << endl;
        } else {
            cout << endl << "Easy Difficulty:" << endl;
        }
        displayTrack(i, _board_players);
        cout << endl;  // Add an extra line between the two lanes
    }
}
void Board::getVectorSize () {
    cout << "Board Players is " << _board_players.size() << endl;
}

char Board::movePlayer(int player_index, int distance) {
    // Increment player position
    _board_players.at(player_index).position += distance ;
    if (_board_players.at(player_index).position >= _BOARD_SIZE-1) {
        _board_players.at(player_index).position = (_BOARD_SIZE-1);
    } else if (_board_players.at(player_index).position < 0) {
        _board_players.at(player_index).position = (0);
    }
    char tileType;

    //Tile type chars are: O (last block), Y (first block), G (grasslands), P (advisor), U (challenge), R (graveyard), N (hyena), B (oasis)
    //Return the character associated with the tile player landed on.
    tileType = _tiles[_board_players.at(player_index).board_type][_board_players.at(player_index).position].color;

    return tileType;
}

int Board::getPlayerPosition(int player_index) {
    //cout << "Players size at playerPosition " << _board_players.size() << endl;
    if (player_index >= 0 && player_index <= _player_count) {
        return _board_players.at(player_index).position;
    }
    return -1;
}