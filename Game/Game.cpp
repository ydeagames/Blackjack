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
	auto& dealer_player = players.back();

	// カード配布
	std::cout << "--> カードを配ります" << std::endl;
	for (auto& player : players)
	{
		auto card = trump.DrawCard();
		if (player->IsDealer())
			card->SetPrivate(true);
		player->AddCard(std::move(card));
		player->AddCard(trump.DrawCard());
		player->Show(main_player);
	}

	std::vector<std::unique_ptr<Player>> done_players;

	// ゲーム開始
	std::cout << "--> ゲーム開始" << std::endl;
	for (auto& player : players)
	{
		std::cout << "! " << player->GetName() << "のターン" << std::endl;
		while (true)
		{
			player->Show(main_player);
			bool choicehit = player->ChooseHit();
			if (choicehit)
			{
				std::cout << "@ ヒット!";
				auto card = trump.DrawCard();
				std::cout << "(Get: ";
				player->ShowCard(main_player, card);
				std::cout << ")" << std::endl;
				player->AddCard(std::move(card));
			}
			else
			{
				std::cout << "@ スタンド" << std::endl;
				break;
			}
			if (player->IsBust())
			{
				std::cout << "× バスト!" << std::endl;
				break;
			}
		}
		player->Show(main_player);
	}

	// リザルト
	std::cout << "--> 結果発表" << std::endl;
	dealer_player->Show(dealer_player);
	for (auto& player : players)
	{
		if (player == dealer_player)
			continue;
		player->Show(player);
		std::cout << player->GetName() << ": ";
		if (player->IsBust() || player->GetTotal() < dealer_player->GetTotal())
			std::cout << "負け";
		else
			std::cout << "勝ち";
		std::cout << std::endl;
	}

	std::cout << "####### ブラックジャックおわり #######" << std::endl;
}