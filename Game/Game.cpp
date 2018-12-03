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
	players.emplace_back(std::make_unique<NormalPlayer>("�v���C���[1"));
	players.emplace_back(std::make_unique<DealerPlayer>());
	auto& main_player = players.front();

	// �J�[�h�z�z
	std::cout << "�J�[�h��z��܂�" << std::endl;
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
		std::cout << player->GetName() << "�̃^�[��" << std::endl;
		while (true)
		{
			player->Show(main_player);
			bool choicehit = player->ChooseHit();
			if (choicehit)
			{
				std::cout << "�q�b�g!" << std::endl;
			}
			else
				break;
			player->AddCard(trump.DrawCard());
			if (player->IsBust())
			{
				std::cout << "�o�X�g!" << std::endl;
				break;
			}
		}
		player->Show(main_player);
	}

	std::cout << "####### �u���b�N�W���b�N����� #######" << std::endl;
}