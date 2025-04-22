#pragma once
#include "Tile.h"
//the logic in this needs to be reworked for balance, I'm also considering changing a lot on how initializeTiles works.

class Board {
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE];
    static const int _MAX_PLAYERS = 2;
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index, int boardType);
    bool isPlayerOnTile(int player_index, int pos);

public:
    Board();
    Board(int player_count);
    void displayTrack(int player_index);
    void initializeBoard(int boardType, int p2BoardType);
    void displayBoard();
    bool movePlayer(int player_index);
    int getPlayerPosition(int player_index) const;
};