#ifndef CPP_GAME_GUI_H
#define CPP_GAME_GUI_H

#include <string>
#include "Board.h"


using namespace std;

class GameGUI {
	static constexpr int CELL_SIZE = 32;
	static constexpr float PADDING = 50.0;
	static constexpr float LINE_THICKNESS = 1.5;

	bool ai_is_making_move = false;


	sf::Font font;
	sf::RenderWindow* window;
	Board board;
	char players;
	char current_player;
	char starting_player;
	vector<bool> players_list;
	int search_depth;

	bool is_user_player(char player);

	void restart_game();
	void restart_game(int size, char players, char starting_player, vector<bool> players_list, int depth);
	void make_move(Point p);
	void make_ai_move();

	void load_font();
	void draw_text(string s, float x, float y);
	void draw_line(sf::Vector2f p0, sf::Vector2f p1, float thickness);
	void draw_line(sf::Vector2f p0, sf::Vector2f p1, float thickness, sf::Color color);

	void draw_player_sign(float x, float y, char player);

	void draw_grid(int size);
	void draw_board(Board board);

	void gameover_screen();

	void handle_click(int x, int y);
	Point compute_coords(int x, int y);



public:

	GameGUI(vector<bool> players_list, int size, int starting_player, int depth);
	void start_gameloop();

};


#endif //CPP_GAME_GUI_H