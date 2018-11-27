#include "Game.h"
#include "Trump.h"
#include "Player.h"
#include "Card.h"

void Game::Start()
{
	std::cout << "########## ブラックジャック ##########" << std::endl;

	// 初期化
	Trump trump = {};	// トランプケースを用意
	trump.Create();		// トランプを用意
	trump.Shuffle();	// トランプをシャッフル

	std::vector<std::unique_ptr<Player>> players;
	players.emplace_back(std::make_unique<NormalPlayer>());
	players.emplace_back(std::make_unique<DealerPlayer>());
	auto& main_player = players.front();

	for (auto& player : players)
	{
		auto card = trump.DrawCard();
		if (player->IsDealer())
			card->SetPrivate(true);
		player->AddCard(std::move(card));
		player->AddCard(trump.DrawCard());
	}

	for (auto& player : players)
	{
		std::cout << player->GetName() << "のターン" << std::endl;
		while (true)
		{
			std::cout << "手札 (" << player->GetTotal() << "pt): ";
			player->Show(main_player);
			if (!player->ChooseHit())
				break;
			player->AddCard(trump.DrawCard());
		}
	}
}