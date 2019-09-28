#include <algorithm>
#include "PiskvorkyEval.h"
#include "GameUtil.h"
#include <iostream>

using namespace std;

int PiskvorkyEval::get_half_closed_score(const vector<char>& line1, char player) {
//    state automata for finding half closed combinations
//    e.g. - - X X X O O
//    or   O O - X X X X
//    must be left-open, right-closed
    int score = 0;

//   half-closed 4 - 100
//   half-closed 3 - 10

//    artificially close the right end of the line

    // line1 is const ref.
    vector<char> line = line1;
    line.push_back(player + 1);
    int counter = 0;
    int state = SEARCHING_FOR_BLANK;

    for (auto const& c : line) {
        if (state == SEARCHING_FOR_BLANK) {
            if(c == Board::BLANK) {
                state = WAITING_FOR_PLAYER_SIGN;
            }
        } else if (state == WAITING_FOR_PLAYER_SIGN) {
            if (c == Board::BLANK) {
//              still no blank, do nothing
            } else if (c == player) {
                state = COUNTING_PLAYER_SIGNS;
                counter = 1;
            } else {
                state = SEARCHING_FOR_BLANK;
            }

        } else if (state == COUNTING_PLAYER_SIGNS) {
            if (c == player) {
                counter += 1;
            } else if (c == Board::BLANK) {
                state = WAITING_FOR_PLAYER_SIGN;
            } else {
//               c is closing sign
                if (counter == 3) {
                    score += 10;
                } else if (counter == 4) {
                    score += 100;
                }
                state = SEARCHING_FOR_BLANK;
            }
        }
    }

    return score;
}

int PiskvorkyEval::get_open_score(const vector<char>& line, char player) {
//    state automata for finding open combinations
//    e.g. - - X X X - O
//    or   - - X X X X - -
//      etc.

    int score = 0;

//   open 4 - win score
//   open 3 - 75
//   open 2 - 10

    int counter = 0;
    int state = SEARCHING_FOR_BLANK;

    for (auto const& c : line) {
        if (state == SEARCHING_FOR_BLANK) {
            if(c == Board::BLANK) {
                state = WAITING_FOR_PLAYER_SIGN;
            }
        } else if (state == WAITING_FOR_PLAYER_SIGN) {
            if (c == Board::BLANK) {
//              still no blank, do nothing
            } else if (c == player) {
                state = COUNTING_PLAYER_SIGNS;
                counter = 1;
            } else {
                state = SEARCHING_FOR_BLANK;
            }

        } else if (state == COUNTING_PLAYER_SIGNS) {
            if (c == player) {
                counter += 1;
            } else if (c == Board::BLANK) {
                if (counter == 2) {
                    score += 10;
                } else if (counter == 3) {
                    score += 75;
                } else if (counter == 4) {
                    score += WIN_SCORE/2;
                } else if (counter == 5) {
                    score += WIN_SCORE;
                }
                state = WAITING_FOR_PLAYER_SIGN;

            } else {
//               c is closing sign
                state = SEARCHING_FOR_BLANK;
            }
        }
    }

    return score;
}

int PiskvorkyEval::get_five_in_row_score(const vector<char>& line, char player) {
    int counter = 0;
    for(char c : line) {
        if (c == player) {
            counter += 1;
        } else {
            counter = 0;
        }

        if (counter == 5) {
            return WIN_SCORE;
        }
    }

    return 0;
}


int PiskvorkyEval::get_line_score(vector<char>& line, char player) {
    int score = 0;
    score += PiskvorkyEval::get_open_score(line, player);
    score += PiskvorkyEval::get_half_closed_score(line, player);


    reverse(line.begin(), line.end());
    score += PiskvorkyEval::get_half_closed_score(line, player);

    score += PiskvorkyEval::get_five_in_row_score(line, player);

    return score;

}

void PiskvorkyEval::print_line(const vector<char>& line) {
    for (auto const& c : line) {
        cout << to_string(c);
    }
    cout << endl;
}

int PiskvorkyEval::eval_board(const Board& board, char player) {
    int score = 0;

    for(auto & line : GameUtil::get_lines(board)) {
        score += PiskvorkyEval::get_line_score(line, player);
    }
    return score;
}

int PiskvorkyEval::eval_board_minimax(const Board& board) {
    int maximizing_player1 = eval_board(board, 1);
    int minimizing_player1 = eval_board(board, 2);
    return maximizing_player1 - minimizing_player1;
}

vector<float> PiskvorkyEval::eval_board_maxn(const Board& board, char players) {
    vector<float> evals;
    for(char i = 1; i <= players; i++) {
        evals.push_back(PiskvorkyEval::eval_board(board,i));
    }

    vector<float> result;
    float sum_rest;
    for(int i = 0; i < players; i++) {

        sum_rest = 0;
        for(int j=0; j < players; j++) {
            if(j != i) {
                sum_rest += evals[j];
            }
        }

        if(sum_rest == 0) {
            sum_rest = 1;
        }
        result.push_back(evals[i] / sum_rest);
    }

    return result;
}