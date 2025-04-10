#include "../headers/Board.h"
#include "../headers/libraries.h"
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"


//init board
void Board::initializeBoard(int boardType, int p2BoardType){
    for (int i = 0; i < 2; i++) {
        if (i==0) {
            initializeTiles(i, boardType); //Ensures unique distribution
          } else {
            initializeTiles(i, p2BoardType);
          }
    }
}

//creates each tile
void Board::initializeTiles(int player_index, int boardType) {
    Tile temp;
    int green_count = 0, special_tiles = 0; //, graveyard = 0, challenge = 0, advisor = 0, hyena = 0, oasis = 0;
    int total_tiles = _BOARD_SIZE, tileType;

    if (boardType == 0) { // straight to pridelands
        for (int i = 0; i < total_tiles; i++) {
            tileType=rand()%20;
            if (i == total_tiles - 1) {
                temp.color = 'O'; //last block orange
            } else if (i == 0) {
                temp.color = 'Y'; //starting block yellow
            } else if (green_count < 20 && rand() % (total_tiles-i) < 20 - green_count) {
                temp.color = 'G'; //grasslands
                green_count++;
            } else if (tileType <= 4 && special_tiles < 30) {
                temp.color = 'P'; // advisors will be pink
                special_tiles++;
                //advisor++;
            } else if (tileType >= 10 && tileType <= 15 && special_tiles < 30) {
                temp.color = 'R'; // red for challenge tile
                special_tiles++;
            } else if (i <= (total_tiles/2) && special_tiles < 30) {
                tileType=rand()%20;
                if (tileType >= 0 && tileType <= 10) {
                    temp.color = 'U'; //purple, for graveyards
                    special_tiles++;
                    //graveyard++;
                } else if (tileType > 10 && tileType <= 15) {
                    temp.color = 'N'; //brown, for hyenas
                    special_tiles++;
                    //hyena++;
                } else if ((tileType) == 18) {
                    temp.color = 'B'; //blue for oasis
                    special_tiles++;
                    //oasis++;
                }
            } else if (i > (total_tiles/2) && special_tiles < 30) {
                tileType=rand()%20;
                if (tileType >= 0 && tileType <= 3) {
                    temp.color = 'U'; //purple, for graveyards
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
            } else if (tileType >= 10 && tileType <= 14) { //20% chance
                temp.color = 'U'; //purple, for graveyards
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
                    temp.color = 'R'; // red for challenge tile
                    special_tiles++;
                }
            } else if (i > (total_tiles/2) && special_tiles < 20) { //second half of the board
                tileType=rand()%20;
                if (tileType >= 0 && tileType <= 3) { //15% chance
                    temp.color = 'B'; //blue for oasis
                    special_tiles++;
                } else if (tileType > 4 && tileType <= 10) { //30% chance
                    temp.color = 'R'; // red for challenge tile
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


// Board::Board()
// {
//     _player_count = 1;

//     // Initialize player position
//     _player_position[0] = 0;

//     // Initialize tiles
//     initializeTiles();
// }

//constructor
Board::Board(int player_count){
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    } else {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles

    initializeBoard(0,0);
}

bool Board::isPlayerOnTile(int player_index, int pos) {
    if (_player_position[player_index] == pos)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int player_index, int pos) {
    // string space = "                                       ";
    string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].color == 'R') {
        color = RED;
    } else if (_tiles[player_index][pos].color == 'G') {
        color = GREEN;
    } else if (_tiles[player_index][pos].color == 'B') {
        color = BLUE;
    } else if (_tiles[player_index][pos].color == 'U') {
        color = PURPLE;
    } else if (_tiles[player_index][pos].color == 'N') {
        color = BROWN;
    } else if (_tiles[player_index][pos].color == 'P') {
        color = PINK;
    } else if (_tiles[player_index][pos].color == 'O') {
        color = ORANGE;
    } else if (_tiles[player_index][pos].color == 'Y') {
        color = GREY;
    }

    if (player == true) {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    } else {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard() {
    for (int i = 0; i < 2; i++)
    {
        displayTrack(i);
        if (i == 0) {
            cout << endl << endl;  // Add an extra line between the two lanes
        }
    }
}

bool Board::movePlayer(int player_index) {
    // Increment player position
    _player_position[player_index]++;
    if (_player_position[player_index] == _BOARD_SIZE - 1) {
        // Player reached last tile
        return true;
    }
    return false;
}

int Board::getPlayerPosition(int player_index) const {
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}