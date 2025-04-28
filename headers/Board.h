#pragma once

#include<vector>

#include "Tile.h"
#include "player.h"
#include "board-player.h"
//the logic in this needs to be reworked for balance, I'm also considering changing a lot on how initializeTiles works.

class Board {
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE]; //_tiles[0] is the board for normal, _tiles[1] is the board for easy
    //static const int _MAX_PLAYERS = 2;
    int _player_count;
    //int _player_position[_MAX_PLAYERS];
    //int _player_arr [2][2]; // pos[x][0] is player position, pos[0][x] is board type
    std::vector<board_player> _board_players;
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index, int boardType);
    bool isPlayerOnTile(int player_index, int pos);

public:
    Board();
    Board(std::vector<Player> players);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    char movePlayer(int player_index, int distance);
    int getPlayerPosition(int player_index);
};