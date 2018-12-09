#include "Game.h"
#include "Blackjack.h"
#include "User.h"

void Game::Start()
{
	// 初期チップ
	int default_balance = 1000;

	// ディーラー
	std::shared_ptr<User> dealer = std::make_shared<User>("ディーラー", default_balance);

	// プレイヤー
	std::shared_ptr<User> player = std::make_shared<User>("あなた", default_balance);
	std::vector<std::shared_ptr<User>> players = { player };

	// ゲームループ
	bool running = true;
	while (running)
	{
		// 試合を初期化
		Blackjack blackjack = { dealer, players };
		// 試合開始
		bool is_exit = blackjack.Start() == -1;

		if (is_exit)
			running = false;
		else
			// 結果
			for (auto& player : players)
			{
				// 結果を表示
				player->ShowChip();
				// 結果にコミット
				player->Commit();
				// 有り金全部溶かしたら終了
				if (player->GetChip() <= 0)
					running = false;
			}
	}

	// 最終結果
	std::cout << "ゲーム終了" << std::endl;
	std::cout << "最終結果" << std::endl;
	for (auto& player : players)
	{
		player->ShowChip(false);
	}
}
