#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Game game = {};
	game.Start();

	std::cin.get();

	return 0;
}