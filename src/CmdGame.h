#ifndef CPP_PISKVKORKY_CMDGAME_H
#define CPP_PISKVKORKY_CMDGAME_H

#include "Board.h"

class CmdGame {
    static constexpr int DEPTH=3;

public:

    // game state
    Board board;
    char current_player;

    CmdGame(const int size, const char starting_player);
    void start_game();
};


#endif //CPP_PISKVKORKY_CMDGAME_H
