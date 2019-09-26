#include "AI_API.h"
#include "PiskvorkyAI.h"
#include <climits>
#include <iostream>

//debug
#include <chrono>

using namespace std;

void AI_API::get_best_move(Board board, char player, char players, int depth, int *move_r, int *move_c) {
    if (players == 2) {
        bool PRUNE = true;
//        minimax

//        benchmark

//        auto start = chrono::high_resolution_clock::now();
//        for(int i=0; i<1000; i++) {
//            int mnm = PiskvorkyEval::eval_board_minimax(board);
//        }
//        auto stop = chrono::high_resolution_clock::now();
//        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//        cout << "Evaluation of board took " <<  duration.count() << endl;


        // auto start = chrono::high_resolution_clock::now();


        PiskvorkyAI ai;
        int score = ai.minimax(board, player, depth, move_r, move_c, INT_MIN, INT_MAX, PRUNE);
        cout << "Ai minimax score: " << score << endl;
        cout << "heuristic function executed " << ai.debug_counter << " times\n";


    } else {
//        TODO maxn algorithm

        PiskvorkyAI ai;
        // vector<float> best_eval = ai.maxn(board, player, players, depth, move_r, move_c);
        vector<float> best_eval = ai.maxn(board, player, players, 3, move_r, move_c);

        cout << "Ai maxn score: " << best_eval[player-1] << endl;
        cout << "heuristic function executed " << ai.debug_counter << " times\n";

    }
}

