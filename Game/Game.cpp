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
	players.emplace_back(std::make_unique<NormalPlayer>("プレイヤー1"));
	players.emplace_back(std::make_unique<DealerPlayer>());
	auto& main_player = players.front();

	// カード配布
	std::cout << "カードを配ります" << std::endl;
	for (auto& player : players)
	{
		auto card = trump.DrawCard();
		if (player->IsDealer())
			card->SetPrivate(true);
		player->AddCard(std::move(card));
		player->AddCard(trump.DrawCard());
		player->Show(main_player);
	}

	for (auto& player : players)
	{
		std::cout << player->GetName() << "のターン" << std::endl;
		while (true)
		{
			player->Show(main_player);
			bool choicehit = player->ChooseHit();
			if (choicehit)
			{
				std::cout << "ヒット!" << std::endl;
			}
			else
				break;
			player->AddCard(trump.DrawCard());
			if (player->IsBust())
			{
				std::cout << "バスト!" << std::endl;
				break;
			}
		}
		player->Show(main_player);
	}

	std::cout << "####### ブラックジャックおわり #######" << std::endl;
}