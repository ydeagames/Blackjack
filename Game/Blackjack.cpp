#include "Blackjack.h"
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "User.h"

int Blackjack::Start()
{
	Sleep(50);

	// 初期化
	Deck trump = {};	// トランプケースを用意
	trump.Create();		// トランプを用意
	trump.Shuffle();	// トランプをシャッフル

	// ユーザーからゲームに参加するプレイヤーを作成
	std::vector<std::shared_ptr<Player>> players;
	for (auto& playerUser : playerUsers)
		players.emplace_back(std::make_shared<NormalPlayer>(playerUser));	// 通常プレイヤー
	players.emplace_back(std::make_shared<DealerPlayer>(dealerUser));		// ディーラープレイヤー

	// 画面の前にいる人 (自分のカードは?にならない)
	auto main_player = players.front();
	// ディーラー
	auto dealer_player = players.back();

	// BET決定
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/card_drag.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> BET設定" << std::endl;
	Sleep(800);
	for (auto& player : players)
	{
		// ディーラーではない人のみがBETできる
		if (!player->IsDealer())
		{
			while (true)
			{
				// チップ
				int chip = player->GetUser()->GetChip();
				std::cout << "  <" << player->GetUser()->GetName() << "のBET額>" << std::endl;
				std::cout << "    BET額を指定してください [-1: ゲームを終了]" << std::endl;

				// 別途BETを入力
				std::cout << "    > ";
				int bet;
				std::cin >> bet;

				// チップ確認
				if (bet > chip)		// 足りない
					std::cout << "    <!> チップが足りません" << std::endl;
				else if (bet == 0)	// 0チップ賭け
					std::cout << "    <!> 1チップ以上かける必要があります" << std::endl;
				else if (bet < 0)	// ゲーム終了
				{
					std::cout << "    (i) ゲームを終了します" << std::endl;
					return -1;
				}
				else				// BET
				{
					std::cout << "    ";
					std::cout << chip << "→";
					// 賭ける
					player->Bet(bet);
					PlaySound(TEXT("Resources/Audio/button3.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(200);
					std::cout << player->GetUser()->GetChip() << "(BET: " << bet << ")" << std::endl;
					Sleep(800);
					break;
				}
				std::cout << std::endl;
			}
		}
	}

	// カード配布
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/card_kubaru.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> カード配布" << std::endl;
	Sleep(800);
	for (auto& player : players)
	{
		// デッキからカードを引く
		auto card = trump.DrawCard();
		// ディーラーの一枚目は伏せる
		if (player->IsDealer())
			card->SetHidden(true);
		// 配る
		player->AddCard(std::move(card));
		player->AddCard(trump.DrawCard());
		std::cout << "  ";
		// 表示する
		player->Show(main_player, 2);
	}

	// ゲーム開始
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/button.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> ゲーム開始" << std::endl;
	Sleep(800);
	for (auto itr = players.begin(); itr != players.end(); ++itr)
	{
		std::shared_ptr<Player> player = *itr;

		std::cout << "  <" << player->GetUser()->GetName() << "のターン>" << std::endl;

		// 有効な選択をするまでループ
		bool choice_running = true;
		while (choice_running)
		{
			std::cout << "    ";
			// 表示
			player->Show(nullptr);
			// 選択
			Choice choicehit = player->Choose(dealer_player);

			// デッキから一枚カードを引く関数
			auto draw_func = [&](std::shared_ptr<Player> player) {
				auto card = trump.DrawCard();
				std::cout << "(Get: ";
				PlaySound(TEXT("Resources/Audio/card_send.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				card->Show(nullptr);
				Sleep(800);
				std::cout << ")";
				player->AddCard(std::move(card));
			};

			std::cout << "    ";
			PlaySound(TEXT("Resources/Audio/card_move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(200);
			// 引いたアクション
			switch (choicehit)
			{
			case Choice::STAND:
				std::cout << "STANDを選びました";
				choice_running = false;
				break;
			case Choice::HIT:
				std::cout << "HITを選びました";
				draw_func(player);
				break;
			case Choice::DOUBLE:
				std::cout << "DOUBLEを選びました";
				draw_func(player);
				// 賭けを2倍にする = 今の賭けだけ賭ける
				player->Bet(player->GetBet());
				choice_running = false;
				break;
			case Choice::SPLIT:
				std::cout << "SPLITを選びました";
				// 分割プレイヤーを作ってこのプレイヤーのあとに挿入する
				{
					auto split = player->Split();
					draw_func(split);
					draw_func(player);
					itr++;
					itr = players.insert(itr, std::move(split));
					itr--;
				}
				break;
			case Choice::INSURANCE:
				std::cout << "INSURANCEを選びました";
				// 賭けを1/2にする
				player->Bet(-player->GetBet() / 2);
				player->insuranced = true;
				break;
			}
			Sleep(800);
			std::cout << std::endl;
			// バスト
			if (player->IsBust())
			{
				std::cout << "    ";
				PlaySound(TEXT("Resources/Audio/button_cancel.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				std::cout << "× BUST!" << std::endl;
				Sleep(800);
				break;
			}
		}
		std::cout << "    ";
		// メインプレイヤーに表示できるものを表示
		player->Show(main_player);
		std::cout << std::endl;
		Sleep(1000);
	}

	// リザルト
	//std::cout << std::endl;
	std::cout << "--> 結果発表" << std::endl;
	PlaySound(TEXT("Resources/Audio/card_mekuru.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "  ";
	// ディーラーの伏せカードも含め結果表示
	dealer_player->Show(nullptr);
	Sleep(800);
	for (auto& player : players)
	{
		if (player == dealer_player)
			continue;
		std::cout << "  <" << player->GetUser()->GetName() << "の結果>" << std::endl;
		std::cout << "    ";
		// プレイヤーのカード再確認
		player->Show(player);
		std::cout << "    ";
		std::cout << player->GetUser()->GetName() << "の勝敗: ";
		int sub;
		// ディーラーのブラックジャック、プレイヤーのバストはプレイヤーの負け
		if (dealer_player->IsBlackjack() || player->IsBust())
			sub = -1;
		// そうでない場合、ディーラーのバストは勝ち
		else if (dealer_player->IsBust())
			sub = 1;
		else
			sub = player->GetPoint(nullptr) - dealer_player->GetPoint(nullptr);
		if (sub < 0)
		{
			PlaySound(TEXT("Resources/Audio/fail.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(200);
			std::cout << "負け";
			Sleep(800);
			player->OnLose();
		}
		else if (sub == 0)
		{
			Sleep(200);
			std::cout << "引き分け";
			Sleep(800);
			player->OnDraw();
		}
		else
		{
			// ブラックジャック
			if (player->IsBlackjack())
			{
				PlaySound(TEXT("Resources/Audio/cheer.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				std::cout << "勝ち(BLACKJACK)";
				Sleep(1600);
			}
			else
			{
				PlaySound(TEXT("Resources/Audio/success.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				std::cout << "勝ち";
				Sleep(800);
			}
			player->OnWin();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
