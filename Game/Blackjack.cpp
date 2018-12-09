#include "Blackjack.h"
#include "Trump.h"
#include "Player.h"
#include "Card.h"
#include "User.h"

void Blackjack::Start()
{
	std::cout << "########## ブラックジャック ##########" << std::endl;

	// 初期化
	Trump trump = {};	// トランプケースを用意
	trump.Create();		// トランプを用意
	trump.Shuffle();	// トランプをシャッフル

	std::vector<std::shared_ptr<Player>> players;
	for (auto& playerUser : playerUsers)
		players.emplace_back(std::make_shared<NormalPlayer>(playerUser));
	players.emplace_back(std::make_shared<DealerPlayer>(dealerUser));
	auto& main_player = players.front();
	auto& dealer_player = players.back();

	// ベット決定
	std::cout << "--> 掛け金設定" << std::endl;
	for (auto& player : players)
	{
		if (!player->IsDealer())
		{
			while (true)
			{
				int chip = player->GetUser()->GetChip();
				int bet;
				std::cout << "ベット額(チップ: " << chip << ")> ";
				std::cin >> bet;
				if (bet <= chip)
				{
					player->Bet(bet);
					break;
				}
				std::cout << "チップが足りません" << std::endl;
			}
		}
	}

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

	std::vector<std::shared_ptr<Player>> done_players;

	// ゲーム開始
	std::cout << "--> ゲーム開始" << std::endl;
	for (auto itr = players.begin(); itr != players.end(); ++itr)
	{
		std::shared_ptr<Player>& player = *itr;

		std::cout << "! " << player->GetUser()->GetName() << "のターン" << std::endl;
		bool choice_running = true;
		while (choice_running)
		{
			player->Show(main_player);
			Choice choicehit = player->Choose(dealer_player);

			auto draw_func = [&](std::shared_ptr<Player> player) {
				auto card = trump.DrawCard();
				std::cout << "(Get: ";
				card->Show(main_player);
				std::cout << ")" << std::endl;
				player->AddCard(std::move(card));
			};

			switch (choicehit)
			{
			case Choice::STAND:
				std::cout << "@ STAND" << std::endl;
				choice_running = false;
				break;
			case Choice::HIT:
				std::cout << "@ HIT!";
				draw_func(player);
				break;
			case Choice::DOUBLE:
				std::cout << "@ DOUBLE!";
				draw_func(player);
				player->Bet(player->GetBet());
				choice_running = false;
				break;
			case Choice::SPLIT:
				std::cout << "@ SPLIT" << std::endl;
				{
					auto split = player->Split();
					draw_func(split);
					draw_func(player);
					itr = players.insert(itr, std::move(split));
				}
				break;
			case Choice::INSURANCE:
				std::cout << "@ INSURANCE" << std::endl;
				player->Bet(-player->GetBet() / 2);
				player->insuranced = true;
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
		std::cout << player->GetUser()->GetName() << ": ";
		int sub = player->GetPoint(nullptr) - dealer_player->GetPoint(nullptr);
		if (player->IsBust() || sub > 0)
		{
			std::cout << "負け";
			player->OnLose();
		}
		else if (sub == 0)
		{
			std::cout << "引き分け";
			player->OnDraw();
		}
		else
		{
			std::cout << "勝ち";
			player->OnWin();
		}
		std::cout << std::endl;
	}

	std::cout << "####### ブラックジャックおわり #######" << std::endl;
}
