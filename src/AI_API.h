
#ifndef CPP_PISKVKORKY_AI_API_H
#define CPP_PISKVKORKY_AI_API_H

#include "Board.h"
#include <iostream>

using namespace std;

class AI_API {
public:
    static void get_best_move(Board board, char player, char players, int depth, int* move_r, int* move_c);
};


#endif //CPP_PISKVKORKY_AI_API_H
