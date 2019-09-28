#ifndef CPP_PISKVKORKY_BOARD_H
#define CPP_PISKVKORKY_BOARD_H

#include <vector>


struct Point {
    int r;
    int c;
};

class Board {
public:
    char *gs;
    int size;
    static constexpr char BLANK = 0;

    // moves are considered only up to REMOTE_DIST distance from some current occupied cell
    static constexpr int REMOTE_DIST = 1;

    Board() = default;

    // construct blank board
    Board(int size);
    ~Board();
    Board& operator= (Board board);

    Board(const Board &b2);

    char get(int r, int c);
    void set(int r, int c, char val);
    std::vector<Point> get_moves();

//    debug method
    static void print_moves(std::vector<Point> moves);

    static bool is_in_board(int r, int c, int size);
    bool is_in_board(int r, int c);
    bool is_remote_cell(int r, int c);

    bool is_board_full();
    char five_in_row();
    bool is_game_over();



};


#endif //CPP_PISKVKORKY_BOARD_H
