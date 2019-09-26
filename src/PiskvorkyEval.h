

#ifndef CPP_PISKVKORKY_PISKVORKYEVAL_H
#define CPP_PISKVKORKY_PISKVORKYEVAL_H

#include "Board.h"

using namespace std;
class PiskvorkyEval {
//    states for pattern-matching state automata
    static const int SEARCHING_FOR_BLANK = 0;
    static const int WAITING_FOR_PLAYER_SIGN = 1;
    static const int COUNTING_PLAYER_SIGNS = 2;

public:

    static const int WIN_SCORE = 1000000;


    static int get_open_score(vector<char> line, char player);
    static int get_half_closed_score(vector<char> line, char player);
    static int get_line_score(vector<char> line, char player);
    static int get_five_in_row_score(vector<char> line, char player);


    static void print_line(vector<char> line);



    static int eval_board(Board board, char player);
    static int eval_board_minimax(Board board);
    static vector<float> eval_board_maxn(Board board, char players);

};


#endif //CPP_PISKVKORKY_PISKVORKYEVAL_H
