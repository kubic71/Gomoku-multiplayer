#include <iostream>
#include "CmdInterface.h"
#include "Board.h"
#include <vector>

using namespace std;

void CmdInterface::print_line(const int size) {
    for(int i = 0; i < (size+1); i++) {
        cout << "- ";
    }
    cout << endl;
}

void CmdInterface::get_user_input(int* row, int* col) {
    cout << "Input space-separated row and col coordinates:\n";
    cin >> *row;
    cin >> *col;
}


void CmdInterface::print_board(Board board) {
    // print top row with number indexes
    cout << "\n  ";
    for(int i=0; i<board.size; i++) {
        cout << i << " ";
    }
    cout << endl;

    print_line(board.size);

    for(int r=0; r<board.size; r++) {
        cout << r << "|";
        for(int c=0; c<board.size; c++)
        {

            cout << to_string(board.get(r, c)) << " ";
        }
        cout << endl;
    }

    print_line(board.size);
}



void CmdInterface::ask_user_for_params(vector<bool>* players, int* size, int* starting_player, int* depth) {
    cout << "How big playing board do you want?: ";
    cin >> *size;

    int n_players;
    cout << "How many players?: ";
    cin >> n_players;

    string choice;
    for(int i = 0; i < n_players; i++) {
        cout << "Player " << i+1 << " human or AI (h/a): ";
        cin >> choice;
        if(choice.front() == 'h') {
            (*players).push_back(true);
        } else {
            (*players).push_back(false);
        }
    }

    cout << "Who do you want to start?: ";
    cin >> *starting_player;

    cout << "How deep do you want to search game tree (d=3 is good default)?: ";
    cin >> *depth;

}