#ifndef CPP_PISKVKORKY_AI_H
#define CPP_PISKVKORKY_AI_H

#include "Board.h"
#include "PiskvorkyEval.h"

class PiskvorkyAI {
public:
    int debug_counter=0;

    int minimax(const Board& board, char player, int depth, int* move_r, int* move_c, int alpha, int beta, bool prune);
    vector<float> maxn(const Board& board, char player, char players, int depth, int *move_r, int *move_c);
};


#endif //CPP_PISKVKORKY_AI_H
