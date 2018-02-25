#ifndef TICTACTOEGAME_HPP
#define TICTACTOEGAME_HPP

#include "GameStatus.hpp"
#include <vector>

class tic_tac_toe_game {
private:
	std::vector<std::vector<char>> board;

public:
	tic_tac_toe_game();

	game_status status;

	std::vector<std::vector<char>> get_board();

	void apply_move(int, int);

	void print_board();


};

#endif