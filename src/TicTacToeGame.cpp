#include "TicTacToeGame.hpp"
#include <iostream>
#include <math.h>

tic_tac_toe_game::tic_tac_toe_game() {
	status = in_progress;

	// initially empty
	board = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'}
	};


}

std::vector<std::vector<char>> tic_tac_toe_game::get_board() {
	return board;
}

void tic_tac_toe_game::apply_move(int player, int pos) {
	pos--;

	if (pos < 0 || status != in_progress) {
		return;
	}

	// calculate the x and y coords of the board for the move
	int x = static_cast<int>(floor(pos / 3));
	int y = pos % 3;

	// if spot isn't empty, exit
	if (board[x][y] == 'X' || board[x][y] == '0') {
		std::cout << "ERROR: illegal move" << std::endl;
		exit(1);
	}

	if (player == 1) {
		board[x][y] = 'X';
	}
	else if (player == 2) {
		board[x][y] = 'O';
	}
	else {
		std::cout << "ERROR: invalid player" << std::endl;
		exit(1);
	}

	// update the game status
	// check if X has won
	if ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') ||
		(board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X') ||
		(board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X') ||
		(board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') ||
		(board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') ||
		(board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X') ||
		(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') ||
		(board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')) {
		status = p1_win;
		return;
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
		status = p2_win;
		return;
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
		status = tie;
		return;
	}
}

void tic_tac_toe_game::print_board() {
	std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;

}
