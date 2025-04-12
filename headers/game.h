#include"libraries.h"
#include"helpers.h"

class Game {
    public:
    void gameMaster ();
    Game();
    private:

    //functions
    void advisorPuller(string filename);
    void characterPuller(string filename);
    void characterSelect();
    void advisorSelect();
    void saveGame();
    void loadGame(string savedGame);


    vector<Characters> characters;
    vector<Advisor> advisors;
};