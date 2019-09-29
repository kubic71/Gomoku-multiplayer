#include <exception>
#include "Board.h"
#include <vector>
#include <iostream>
#include "GameUtil.h"


using namespace std;


struct OutOfBoundsException : public exception {
    const char *what() const throw() {
        return "Coordinates out of bounds!";
    }
};


Board::Board(int size) {

    for(int i=0; i<size*size; i++) {
        gs.push_back(0);
    }

    this->size = size;
}



char Board::get(int r, int c) const {
    return gs[r*size + c];
}

void Board::set(int r, int c, char val) {
    if(r < 0 || c < 0 || r > size || c > size) {
        throw OutOfBoundsException();
    }
    gs[r*size + c] = val;
}

// return all possible moves at current game state
// to keep branching factor low, consider only moves that are at most 2 cells away from some occupied cell
vector<Point> Board::get_moves() const {
    vector<Point> moves;

    for(int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            if (get(r, c) == BLANK && !is_remote_cell(r, c)) {
                moves.push_back(Point{r, c});
            }
        }
    }

//    when board is empty
    if (moves.empty()) {
        moves.push_back(Point{size/2, size/2});
    }

    return moves;
}

bool Board::is_remote_cell(int r, int c) const {
    for(int r1 = r - REMOTE_DIST; r1 <= r + REMOTE_DIST; r1++) {
        for(int c1 = c - REMOTE_DIST; c1 <= c + REMOTE_DIST; c1++) {
            if (is_in_board(r1, c1) && get(r1, c1) != BLANK) {
                return false;
            }
        }
    }
    return true;
}

bool Board::is_in_board(int r, int c, int size) {
        return r >= 0 && r < size && c >= 0 && c < size;
}

bool Board::is_in_board(int r, int c) const {
    return r >= 0 && r < size && c >= 0 && c < size;
}

void Board::print_moves(const vector<Point>& moves) {
    for(auto const& move: moves) {
        cout << move.r << " " << move.c << endl;
    }
}


bool Board::is_board_full() const {
    for(int r=0; r<size; r++) {
        for(int c=0; c<size; c++) {
            if (get(r, c) == 0) {
                return false;
            }
        }
    }

    return true;
}


char Board::five_in_row() const {
    vector<vector<char>> lines = GameUtil::get_lines(*this);
    int in_row;
    for(auto const& line : lines) {
         in_row = 0;
        char prev = BLANK;
        for(char c : line) {
            if (c == prev) {
                in_row++;
            } else {
//                reset counter
                prev = c;
                in_row = 1;
            }

            if (in_row == 5 && c != BLANK) {
                return true;
            }
        }
    }

    return false;
}

bool Board::is_game_over() const {
    return five_in_row() || is_board_full();

}










