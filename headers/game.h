#pragma once
//this essentially replaces the old "guard" ifndef & define statements.
// This ensures these definitions are only included once on compile, and
// prevents errors coming from the compiler trying to figure out why I keep
// redefining everything.

#include"libraries.h"
#include"helpers.h"

/* this is it, the functions where everything happens!

BLUF:

In here, I want to have a function which tracks the location of all players and does the board display function, and
functions to split the text files up into vectors of characters, advisors, riddles, and events.

Variable-wise, I want vectors of players, characters, advisors, riddles, and events.

I then want two functions: gamemasterInit and gamemaster. GMI will do the printing of a character array, some flavor
text, and the "select character" and "select path" menu.

Gamemaster will essentially act as a turn, returning the value of the next player's turn (i.e. if player 1 just played, it'll
return the value for Player 2). In theory, GM should open the player menu, move the player, handle events (both tile and random),
possibly integrate a combat system, then hand it off to the second player.

Finally, I want a endgame function. This displays stats between the two players and tells us who's the winner.
*/

class Game {
    public:
    //game function
    int gameMaster (int player);
    void gameMasterInit ();

    //constructor
    Game();
    Game(int playerNumber, string eventsFile, string advisorFile, string characterFile, string riddleFile);

    private:
    //functions
    void advisorPuller(string filename);
    void characterPuller(string filename);
    void characterSelect();
    void advisorSelect();
    void saveGame();
    void loadGame(string savedGame);

    //variables
    vector<Characters> characters;
    vector<Advisor> advisors;
};