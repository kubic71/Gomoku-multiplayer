#include "GameUtil.h"

#include <iostream>
#include <vector>


char GameUtil::next_player(char current_player, char players) {
    return (current_player % players) + 1;
}


vector<vector<char>> GameUtil::get_rows(Board board, bool flip) {
    vector<vector<char>> rows;
    for (int r = 0; r < board.size; r++) {
        vector<char> row;
        for (int c = 0; c < board.size; c++) {
            if (flip) {
                row.push_back(board.get(c, r));
            } else {
                row.push_back(board.get(r, c));
            }
        }

        rows.push_back(row);
    }

    return rows;
}


vector<vector<char>> GameUtil::get_rows(Board board) {
    return GameUtil::get_rows(board, false);
}

vector<vector<char>> GameUtil::get_columns(Board board) {
    return GameUtil::get_rows(board, true);
}

vector<vector<char>> GameUtil::get_diagonals(Board board, bool flip) {
    vector<vector<char>> diags;

    int r;
    for (int r_ind = 1; r_ind < 2 * board.size - 2; r_ind++) {
        r = r_ind;

        vector<char> diag;
        int c = 0;
        while (!board.is_in_board(r, c)) {
            r -= 1;
            c += 1;
        }

        while (board.is_in_board(r, c)) {
            if (flip) {
                diag.push_back(board.get(r, board.size - 1 - c));
            } else {
                diag.push_back(board.get(r, c));
            }

            r -= 1;
            c += 1;
        }

        diags.push_back(diag);
    }

    return diags;
}

vector<vector<char>> GameUtil::get_lines(Board board) {
    vector<vector<char>> rows = GameUtil::get_rows(board);
    vector<vector<char>> cols = GameUtil::get_columns(board);
    vector<vector<char>> diags1 = GameUtil::get_diagonals(board, false);
    vector<vector<char>> diags2 = GameUtil::get_diagonals(board, true);

    vector<vector<char>> lines;

    lines.insert(lines.end(), rows.begin(), rows.end());
    lines.insert(lines.end(), cols.begin(), cols.end());
    lines.insert(lines.end(), diags1.begin(), diags1.end());
    lines.insert(lines.end(), diags2.begin(), diags2.end());

    return lines;
}



