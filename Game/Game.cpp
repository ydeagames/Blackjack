#include "Game.h"
#include "Trump.h"
#include "Player.h"
#include "Card.h"

void Game::Start()
{
	std::cout << "########## �u���b�N�W���b�N ##########" << std::endl;

	// ������
	Trump trump = {};	// �g�����v�P�[�X��p��
	trump.Create();		// �g�����v��p��
	trump.Shuffle();	// �g�����v���V���b�t��

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
		std::cout << player->GetName() << "�̃^�[��" << std::endl;
		while (true)
		{
			std::cout << "��D (" << player->GetTotal() << "pt): ";
			player->Show(main_player);
			if (!player->ChooseHit())
				break;
			player->AddCard(trump.DrawCard());
		}
	}
}