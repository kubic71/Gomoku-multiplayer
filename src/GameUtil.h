#ifndef CPP_PISKVKORKY_GAMEUTIL_H
#define CPP_PISKVKORKY_GAMEUTIL_H
#include <vector>
#include <memory>
#include "Board.h"

using namespace std;
class GameUtil {
private:
    static vector<vector<char>> get_rows(const Board& board, bool flip);
    static vector<vector<char>> get_rows(const Board& board);
    static vector<vector<char>> get_columns(const Board& board);
    static vector<vector<char>> get_diagonals(const Board& board, bool flip);


public:
    static char next_player(char current_player, char players);

    // return all possible rows, columns and diagonals from the board to be used by evaluating function, game_over function etc.
    static vector<vector<char>> get_lines(const Board& board);
};


#endif //CPP_PISKVKORKY_GAMEUTIL_H
