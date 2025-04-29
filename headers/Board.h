#pragma once

#include<vector>

#include "Tile.h"
#include "player.h"
#include "board-player.h"
//the logic in this needs to be reworked for balance, I'm also considering changing a lot on how initializeTiles works.

class Board {
private:
    //tile info
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE]; //_tiles[0] is the board for normal, _tiles[1] is the board for easy
    
    //player information
    int _player_count;
    std::vector<board_player> _board_players;

    //display work
    void displayTile(int player_index, int pos, std::vector<board_player> players);
    void initializeTiles(int player_index, int boardType);

public:
    //constructors
    Board();
    Board(std::vector<Player> players);
    
    //interactable display info
    void displayTrack(int player_index, std::vector<board_player> players);
    void initializeBoard();
    void displayBoard();

    //playerpos information
    char movePlayer(int player_index, int distance);
    int getPlayerPosition(int player_index);

    //debugging cout tool
    void getVectorSize();
};