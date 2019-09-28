
#include "CmdGame.h"
#include "CmdInterface.h"
#include "GameUtil.h"
#include <iostream>
#include "AI_API.h"


using namespace std;

CmdGame::CmdGame(const int size, const char starting_player) {
    board = Board(size);
    current_player = starting_player;
}
void CmdGame::start_game() {

    while (!board.is_game_over()) {
        CmdInterface :: print_board(board);

        cout << "player " << to_string(current_player) << " on move" << endl;

        if (current_player == 1) {
//            human player
            int r, c;
            CmdInterface::get_user_input(&r, &c);
            if (board.is_in_board(r, c) && (board.get(r, c) == Board::BLANK)) {
                board.set(r, c, current_player);
                current_player = GameUtil::next_player(current_player, 2);
            } else {
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

