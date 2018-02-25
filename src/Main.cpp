#include <iostream>
#include "GameAgent.hpp"
#include "PlayerType.hpp"

using namespace std;

int main() {
	// create a new agent with the specified player types
	auto* agent = new game_agent(human, ai);

	// run the agent, which in turn runs the game
	agent->run();

	delete agent;

	return 0;
}
