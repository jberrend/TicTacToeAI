#include "GameAgent.hpp"
#include "TicTacToeGame.hpp"
#include "GameStatus.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

game_agent::game_agent(player_type p1, player_type p2) {
	player_one_type_ = p1;
	player_two_type_ = p2;

	current_turn_ = 1; // player one starts

	ai_player_ = -1;
	best_move_ = -1;
}

void game_agent::run() {
	auto* game = new tic_tac_toe_game();

	while (game->status == in_progress) {

		// clear the console window - platform specific
#if WIN32
		system("cls");
#endif

#if __linux__
		system("clear");
#endif

		game->print_board();

		if (current_turn_ == 1) {
			if (player_one_type_ == ai) {
				int move = find_move(game->get_board(), 1);
				game->apply_move(1, move);
			}
			else {
				game->apply_move(1, ask_for_move());
			}

			current_turn_ = 2;
		}
		if (game->status != in_progress) {
			continue; 
		}

		else if (current_turn_ == 2) {
			if (player_two_type_ == ai) {
				int move = find_move(game->get_board(), 2);
				game->apply_move(2, move);
			}
			else {
				game->apply_move(2, ask_for_move());
			}

			current_turn_ = 1;
		}

	}

	// when we get here, the game should have ended with either a winner or a tie
	switch (game->status) {
	case p1_win:
		std::cout << "Player 1 wins!" << std::endl;
		break;

	case p2_win:
		std::cout << "Player 2 wins!" << std::endl;
		break;

	case tie:
		std::cout << "Game tied!" << std::endl;
		break;

	default:
		std::cout << "what da heck?" << std::endl;
		break;
	}

	delete game;

	char c;
	std::cin >> c;
}


// the fun part
int game_agent::find_move(std::vector<std::vector<char>> board, int player) {
	ai_player_ = player;
	best_move_ = -1; // initialize so we know if nothing was found
	max_value(board, player, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0);


	return best_move_ + 1;
}

int game_agent::max_value(std::vector<std::vector<char>> board, int player, int alpha, int beta, int depth) {
	// if the game is over...
	int status = get_board_status(board);
	if (status != in_progress) {
		if (status == p1_win && ai_player_ == 1) {
			// std::cout << "found end state max" << std::endl;
			return 100 - depth;
		}
		if (status == p2_win && ai_player_ == 2) {
			// std::cout << "found end state max" << std::endl;
			return 100 - depth;
		}
		if (status == tie) {
			return 0;
		}

		return -100;
	}

	int v = std::numeric_limits<int>::min();
	int index = -100; // some arbitrary value
	int nextPlayer = player == 1 ? 2 : 1;


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// if the move is legal (not X or O)
			if (board[i][j] != 'X' && board[i][j] != 'O') {
				int prevV = v;
				v = std::max(v, min_value(apply_move(player, i, j, board), nextPlayer, alpha, beta, depth + 1));
				if (v != prevV) {
					index = i * 3 + j;
				}

				if (v >= beta) {
					best_move_ = index;
					return v;
				}

				alpha = std::max(alpha, v);
			}
		}
	}

	best_move_ = index;
	return v;
}

int game_agent::min_value(std::vector<std::vector<char>> board, int player, int alpha, int beta, int depth) {
	// if the game is over...
	int status = get_board_status(board);
	if (status != in_progress) {
		if (status == p1_win && ai_player_ == 1) {
			// std::cout << "found end state min" << std::endl;
			return 100 - depth;
		}
		if (status == p2_win && ai_player_ == 2) {
			// std::cout << "found end state min" << std::endl;
			return 100 - depth;
		}
		if (status == tie) {
			return 0;
		}

		return -1000;
	}

	int v = std::numeric_limits<int>::max();
	int index = -100;
	int nextPlayer = player == 1 ? 2 : 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// if the move is legal (not X or O)
			if (board[i][j] != 'X' && board[i][j] != 'O') {

				int prevV = v;
				v = std::min(v, max_value(apply_move(player, i, j, board), nextPlayer, alpha, beta, depth + 1));
				if (v != prevV) {
					index = i * 3 + j;
				}

				if (v <= alpha) {
					best_move_ = index;
					// std::cout << "pruned v: " << v << " best move " << bestMove << std::endl;
					return v;
				}

				beta = std::min(beta, v);
			}
		}
	}

	best_move_ = index;
	// std::cout << "v:        " << v << " best move: " << bestMove << std::endl;
	return v;
}


int game_agent::ask_for_move() {
	std::cout << "where would you like to place your move?" << std::endl;

	int move;

	std::cin >> move;

	if (move < 1 || move > 9) {
		std::cout << "please enter a valid move" << std::endl << std::endl;
		return ask_for_move();
	}
	return move;
}

int game_agent::get_board_status(std::vector<std::vector<char>> board) {
	if ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') ||
		(board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X') ||
		(board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X') ||
		(board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') ||
		(board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') ||
		(board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X') ||
		(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') ||
		(board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')) {
		return p1_win;
	}

	// check if O has won
	if ((board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') ||
		(board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O') ||
		(board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O') ||
		(board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') ||
		(board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O') ||
		(board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O') ||
		(board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') ||
		(board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O')) {
		return p2_win;
	}

	// check for draw
	bool draw = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != 'X' && board[i][j] != 'O') {
				draw = false;
			}
		}
	}

	if (draw) {
		return tie;
	}

	return in_progress;
}

std::vector<std::vector<char>> game_agent::apply_move(int player, int x, int y, std::vector<std::vector<char>> board) {
	if (board[x][y] == 'X' || board[x][y] == 'O') {
		return std::vector<std::vector<char>>();
	}

	if (player == 1) {
		board[x][y] = 'X';
	}

	else {
		board[x][y] = 'O';
	}

	return board;
}

