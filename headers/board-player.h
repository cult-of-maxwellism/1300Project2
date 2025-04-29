#pragma once
#include<string>
//this struct exists mostly to save memory for the Board class. Also, it's mentally easier than a struct of just straight players.
struct board_player {
    int position;
    int board_type;
    bool onTile;
};