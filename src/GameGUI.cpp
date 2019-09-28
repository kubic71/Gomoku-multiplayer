#include "GameGUI.h"
#include <iostream>
#include <string>
#include <thread>
#include "GameUtil.h"
#include "AI_API.h"

using namespace std;

GameGUI::GameGUI(vector<bool> players_list, int size, int starting_player, int depth)
{
	load_font();
	restart_game(size, players_list.size(), starting_player, players_list, depth);
}

void GameGUI::load_font()
{
	string font_file = "assets/arial.ttf";
	if (!font.loadFromFile(font_file))
	{
		cout << "failed to load font " << font_file;
	}
	else
	{
		cout << font_file << " successfully loaded!" << endl;
	}
}

// restart game with the same params
void GameGUI::restart_game()
{
	restart_game(board.size, players, starting_player, players_list, search_depth);
}

void GameGUI::restart_game(int size, char n_players, char starting_player, vector<bool> players_list, int depth)
{
	search_depth = depth;
	board = Board(size);
	this->starting_player = starting_player;
	this->players_list = players_list;
	current_player = starting_player;
	ai_is_making_move = false;
	players = n_players;
}

void GameGUI::draw_text(string s, float x, float y)
{
	sf::Text text;
	text.setPosition(sf::Vector2f(x, y));
	text.setFont(font);
	text.setString(s);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	window->draw(text);
}

void GameGUI::draw_line(sf::Vector2f p0, sf::Vector2f p1, float thickness)
{
	draw_line(p0, p1, thickness, sf::Color::Black);
}

void GameGUI::draw_line(sf::Vector2f p0, sf::Vector2f p1, float thickness, sf::Color color)
{
	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setFillColor(color);

	sf::Vector2f line = p1 - p0;
	sf::Vector2f normal = sf::Vector2f(-line.y, line.x);

	// normalize
	float length = sqrt(normal.x * normal.x + normal.y * normal.y);
	normal.x = normal.x / length;
	normal.y = normal.y / length;

	sf::Vector2f a = p0 - thickness * normal;
	sf::Vector2f b = p0 + thickness * normal;
	sf::Vector2f c = p1 + thickness * normal;
	sf::Vector2f d = p1 - thickness * normal;

	convex.setPoint(0, a);
	convex.setPoint(1, b);
	convex.setPoint(2, c);
	convex.setPoint(3, d);

	window->draw(convex);
}

void GameGUI::draw_board(Board board)
{
	draw_grid(board.size);

	// draw elemnts on the board
	for (int r = 0; r < board.size; r++)
	{
		for (int c = 0; c < board.size; c++)
		{
			float xcoord = PADDING + c * CELL_SIZE;
			float ycoord = PADDING + r * CELL_SIZE;
			if (board.get(r, c) != Board::BLANK)
			{
				draw_player_sign(xcoord, ycoord, board.get(r, c));
			}
		}
	}
}

void GameGUI::draw_player_sign(float x, float y, char player)
{
	if (player == 1)
	{
		// draw X
		draw_line(sf::Vector2f(x + 5, y + 5), sf::Vector2f(x + CELL_SIZE - 5, y + CELL_SIZE - 5), 3, sf::Color::Red);
		draw_line(sf::Vector2f(x + CELL_SIZE - 5, y + 5), sf::Vector2f(x + 5, y + CELL_SIZE - 5), 3, sf::Color::Red);
	}
	else if (player == 2)
	{
		// draw O
		sf::CircleShape shape(CELL_SIZE / 2 - 2);
		shape.setPosition(sf::Vector2f(x + 1, y + 1));
		shape.setFillColor(sf::Color::White);
		shape.setOutlineThickness(-6.f);
		shape.setOutlineColor(sf::Color::Blue);

		window->draw(shape);
	}
	else
	{
		draw_text(to_string(player), x + LINE_THICKNESS + CELL_SIZE / 2 - 9, y + LINE_THICKNESS);
	}
}

void GameGUI::draw_grid(int size)
{

	for (int i = 0; i <= size; i++)
	{
		// horizontal line
		draw_line(sf::Vector2f(PADDING, PADDING + i * CELL_SIZE), sf::Vector2f(PADDING + size * CELL_SIZE, PADDING + i * CELL_SIZE), LINE_THICKNESS);

		// vertical line
		draw_line(sf::Vector2f(PADDING + i * CELL_SIZE, PADDING), sf::Vector2f(PADDING + i * CELL_SIZE, PADDING + size * CELL_SIZE), LINE_THICKNESS);
	}
}

Point GameGUI::compute_coords(int x, int y)
{
	Point p;
	p.c = (x - PADDING) / CELL_SIZE;
	p.r = (y - PADDING) / CELL_SIZE;
	return p;
}

void GameGUI::handle_click(int x, int y)
{

	if (is_user_player(current_player))
	{
		Point p = compute_coords(x, y);

		// if clicked inside playing board
		if (board.is_in_board(p.r, p.c))
		{
			make_move(p);
		}
		else
		{
			// clicked outside of playing board
		}
	}
}

void GameGUI::make_move(Point p)
{
	if (board.get(p.r, p.c) == Board::BLANK)
	{
		board.set(p.r, p.c, current_player);
		current_player = GameUtil::next_player(current_player, players);
	}
}

void GameGUI::make_ai_move()
{
	int r, c;
	AI_API::get_best_move(board, current_player, players, search_depth, &r, &c);
	board.set(r, c, current_player);
	current_player = GameUtil::next_player(current_player, players);
	ai_is_making_move = false;
}

bool GameGUI::is_user_player(char player)
{
	return players_list[player - 1];
}

void GameGUI::gameover_screen()
{
	while (window->isOpen())
	{
		window->clear(sf::Color::White);
		draw_board(board);
		draw_text("Gameover!", PADDING, CELL_SIZE * board.size + PADDING + 30);
		window->display();

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::MouseButtonPressed:
				restart_game();
				return;

			default:
				break;
			}
		}
	}
}

void GameGUI::start_gameloop()
{

	window = new sf::RenderWindow(sf::VideoMode(2*PADDING + CELL_SIZE * board.size, 3*PADDING + CELL_SIZE * board.size), "Piskvorky");
	std::thread ai_thread;

	while (window->isOpen())
	{
		if (board.is_game_over())
		{
			// restart with the same parameters
			gameover_screen();
			restart_game();
		}

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				cout << "exiting";
				window->close();
				break;
			case sf::Event::Resized:
			{
				window->setSize(sf::Vector2u(event.size.width, event.size.height));
			}
			break;

			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					handle_click(event.mouseButton.x, event.mouseButton.y);
				}
			}
			break;

			default:
				break;
			}
		}

		window->clear(sf::Color::White);

		if (is_user_player(current_player))
		{
			draw_text("Player " + to_string(current_player) + " moves", PADDING, CELL_SIZE * board.size + PADDING + 30);
		}
		else
		{
			// ai
			if (ai_is_making_move)
			{
				draw_text("AI Player " + to_string(current_player) + " moves", PADDING, CELL_SIZE * board.size + PADDING + 30);
			}
			else
			{
				// ai needs to make move
				ai_is_making_move = true;
				ai_thread = std::thread(&GameGUI::make_ai_move, this);
				ai_thread.detach();
			}
		}
		draw_board(board);
		window->display();
	}
}
