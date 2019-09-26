#include "Board.h"
#include <vector>

#ifndef CPP_PISKVKORKY_CMD_INTERFACE_CPP_H
#define CPP_PISKVKORKY_CMD_INTERFACE_CPP_H

using namespace std;
class CmdInterface {
private:
    void static print_line(const int size);

public:
    void static print_board(Board board);
    void static get_user_input(int* row, int* col);
    void static ask_user_for_params(vector<bool>* players, int* size, int* starting_player, int* depth);
};

#endif //CPP_PISKVKORKY_CMD_INTERFACE_CPP_H
