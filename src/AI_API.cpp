#include "AI_API.h"
#include "PiskvorkyAI.h"
#include <climits>
#include <iostream>

using namespace std;

void AI_API::get_best_move(const Board& board, char player, char players, int depth, int *move_r, int *move_c) {
    if (players == 2) {
        bool PRUNE = true;

        PiskvorkyAI ai;
        int score = ai.minimax(board, player, depth, move_r, move_c, INT_MIN, INT_MAX, PRUNE);
        cout << "Ai minimax score: " << score << endl;
        cout << "heuristic function executed " << ai.debug_counter << " times\n";


    } else {

        PiskvorkyAI ai;
        vector<float> best_eval = ai.maxn(board, player, players, depth, move_r, move_c);

        cout << "Ai maxn score: " << best_eval[player-1] << endl;
        cout << "heuristic function executed " << ai.debug_counter << " times\n";

    }
}

