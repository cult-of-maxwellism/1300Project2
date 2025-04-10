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
    int green_count = 0, graveyard = 0, challenge = 0, hyena = 0, oasis = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++) {
        //chanceNum = rand()%100;
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } else if (i == 0) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'Y';
        } else if (boardType == 0) {  //Pridelands!
            if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
                temp.color = 'G';
                green_count++;
            }
                int color_choice = rand() % 5;
                switch (color_choice) {
                    case 0:
                        temp.color = 'B'; // Blue
                        break;
                    case 1:
                        temp.color = 'P'; // Pink
                        break;
                    case 2:
                        temp.color = 'N'; // Brown
                        break;
                    case 3:
                        temp.color = 'R'; // Red
                        break;
                    case 4:
                        temp.color = 'U'; // Purple
                        break;
                }
                // Assign the tile to the board for the specified lane
            _tiles[player_index][i] = temp;
        } else if (boardType == 1) { //cub training
            if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
                temp.color = 'G';
                green_count++;
            }
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice) {
                case 0:
                    temp.color = 'B'; // Blue
                    break;
                case 1:
                    temp.color = 'P'; // Pink
                    break;
                case 2:
                    temp.color = 'N'; // Brown
                    break;
                case 3:
                    temp.color = 'R'; // Red
                    break;
                case 4:
                    temp.color = 'U'; // Purple
                    break;
            }
        }
        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
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