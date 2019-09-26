
#include "CmdGame.h"
#include "CmdInterface.h"
#include "GameUtil.h"
#include <iostream>
#include "AI_API.h"

// for debug purposes only
#include "PiskvorkyEval.h"

using namespace std;

CmdGame::CmdGame(const int size, const char starting_player) {
    board = Board(size);
    current_player = starting_player;
}
void CmdGame::start_game() {
//      0 1 2 3 4 5
//    -------------
//    0|2 2 1 2 2 0
//    1|0 1 2 0 0 0
//    2|1 1 1 1 0 0
//    3|0 0 2 1 0 0
//    4|0 0 0 0 0 0
//    5|0 0 0 0 0 0
//
//    board.set(0, 0, 2);
//    board.set(0, 1, 2);
//    board.set(0, 2, 1);
//    board.set(0, 3, 2);
//    board.set(0, 4, 2);
//    board.set(1 , 1 , 1);
//    board.set( 1, 2, 2);
//    board.set( 2,0 , 1);
//    board.set( 2, 1, 1);
//    board.set( 2, 2, 1);
//    board.set( 2, 3, 1);
//    board.set( 3, 2, 2);
//    board.set( 3, 3, 1);
//    board.set( , , );
//    board.set( , , );


    while (!board.is_game_over()) {
        CmdInterface :: print_board(board);

//      debug
//        vector<char> v1 = {2, 0, 1, 1 ,0, 0};
//        PiskvorkyEval::get_line_score(v1, 1);

        cout << "player " << to_string(current_player) << " on move" << endl;
        cout << "eval board for player 1:" << PiskvorkyEval::eval_board(board, 1) << endl;

        if (current_player == 1) {
//            human player
            int r, c;
            CmdInterface::get_user_input(&r, &c);
            if (board.is_in_board(r, c) && (board.get(r, c) == Board::BLANK)) {
                board.set(r, c, current_player);
                current_player = GameUtil::next_player(current_player, 2);
            } else {
//                invalid move
                cout << "Invalid move!";
            }

        } else {
//          ai move

            int r, c;
            AI_API::get_best_move(board, current_player, 2, DEPTH, &r, &c);
            board.set(r, c, current_player);


            current_player = GameUtil::next_player(current_player, 2);
        }

    }

    CmdInterface :: print_board(board);
    cout << "Game over!" << endl;
}

