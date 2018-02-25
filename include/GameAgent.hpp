#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP

#include "PlayerType.hpp"
#include <vector>

class game_agent {
public:
	game_agent(player_type, player_type);
	void run();
	int find_move(std::vector<std::vector<char>>, int);
	
private:
	// what type of player each is - bot or human
	player_type player_one_type_;
	player_type player_two_type_;

	// which player the AI is playing as
	int ai_player_;

	// who has the current turn in the game, 1 or 2
	int current_turn_;

	int ask_for_move();

	int get_board_status(std::vector<std::vector<char>> board);

	// applies a given move to a given board as a given player
	std::vector<std::vector<char>> apply_move(int player, int x, int y, std::vector<std::vector<char>> board);

	int best_move_;
	int max_value(std::vector<std::vector<char>> board, int player, int alpha, int beta, int depth);
	int min_value(std::vector<std::vector<char>> board, int player, int alpha, int beta, int depth);

};


#endif