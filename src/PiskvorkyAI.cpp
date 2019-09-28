#include "PiskvorkyAI.h"
#include <climits>
#include <algorithm>
#include "GameUtil.h"

using namespace std;

int PiskvorkyAI::minimax(Board board, char player, int depth, int *move_r, int *move_c, int alpha, int beta, bool prune)
{
    if (depth == 0 || board.is_game_over())
    {
        debug_counter += 1;
        return PiskvorkyEval::eval_board_minimax(board);
    }

    //    maximizing player
    int best_val;
    int new_val;
    Point best_move;
    if (player == 1)
    {
        best_val = INT_MIN;

        for (Point move : board.get_moves())
        {
            Board new_board = board;
            new_board.set(move.r, move.c, player);
            new_val = minimax(new_board, 2, depth - 1, nullptr, nullptr, alpha, beta, prune);

            if (new_val > best_val)
            {
                best_val = new_val;
                best_move = move;
            }

            if (prune)
            {
                alpha = max(alpha, best_val);
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
    }
    else
    {
        //    minimizing player
        best_val = INT_MAX;

        for (Point move : board.get_moves())
        {
            Board new_board = board;
            new_board.set(move.r, move.c, player);
            new_val = minimax(new_board, 1, depth - 1, nullptr, nullptr, alpha, beta, prune);

            if (new_val < best_val)
            {
                best_val = new_val;
                best_move = move;
            }

            if (prune)
            {
                beta = min(beta, best_val);
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
    }

    //  if it's first level of recursion, return best move
    if (move_r != nullptr)
    {
        *move_r = best_move.r;
        *move_c = best_move.c;
    }

    return best_val;
}

vector<float> PiskvorkyAI::maxn(Board board, char player, char players, int depth, int *move_r, int *move_c)
{
    if (depth == 0 || board.is_game_over())
    {
        debug_counter += 1;
        vector<float> eval = PiskvorkyEval::eval_board_maxn(board, players);
        return eval;
    }

    float best_val = INT_MIN;
    vector<float> best_eval;
    vector<float> new_eval;
    Point best_move;
    int player_index = player - 1;

    for (Point move : board.get_moves())
    {
        Board new_board = board;
        new_board.set(move.r, move.c, player);
        new_eval = maxn(new_board, GameUtil::next_player(player, players), players, depth - 1, nullptr, nullptr);


        if (new_eval[player_index] > best_val)
        {
            best_val = new_eval[player_index];
            best_eval = new_eval;
            best_move = move;
        }
    }

    if (move_r != nullptr)
    {
        *move_r = best_move.r;
        *move_c = best_move.c;
    }

    return best_eval;

}
