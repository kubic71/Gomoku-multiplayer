#include <iostream>
#include "CmdGame.h"
#include "GameGUI.h"
#include "CmdInterface.h"

using namespace std;



int main() {
    // CMD mode is only for 2 players
    bool CMD_MODE = false;


    // vector of human/AI flags, true = human player, false = AI
    vector<bool> players;
    int size;
    int starting_player;
    int depth;

    CmdInterface::ask_user_for_params(&players, &size, &starting_player, &depth);

    if(CMD_MODE) {
        CmdGame game(10, 1);
        game.start_game();
    } else {
        GameGUI gui(players, size, starting_player, depth);
        gui.start_gameloop();
        cout << "The end";
    }



    return 0;
}


