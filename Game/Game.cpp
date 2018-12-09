#include "Game.h"
#include "Blackjack.h"
#include "User.h"

void Game::Start()
{
	int default_balance = 1000;
	std::shared_ptr<User> dealer = std::make_shared<User>("カリスマディーラー", default_balance);
	std::shared_ptr<User> player = std::make_shared<User>("あなた", default_balance);

	std::vector<std::shared_ptr<User>> players = { player };

	bool running = true;
	while (running)
	{
		Blackjack blackjack = { dealer, players };
		blackjack.Start();

		for (auto& player : players)
		{
			player->ShowChip();
			player->Commit();
			if (player->GetChip() <= 0)
				running = false;
		}
	}
}
