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
	auto& dealer_player = players.back();

	// �J�[�h�z�z
	std::cout << "--> �J�[�h��z��܂�" << std::endl;
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

	// �Q�[���J�n
	std::cout << "--> �Q�[���J�n" << std::endl;
	for (auto& player : players)
	{
		std::cout << "! " << player->GetName() << "�̃^�[��" << std::endl;
		while (true)
		{
			player->Show(main_player);
			bool choicehit = player->ChooseHit();
			if (choicehit)
			{
				std::cout << "@ �q�b�g!";
				auto card = trump.DrawCard();
				std::cout << "(Get: ";
				player->ShowCard(main_player, card);
				std::cout << ")" << std::endl;
				player->AddCard(std::move(card));
			}
			else
			{
				std::cout << "@ �X�^���h" << std::endl;
				break;
			}
			if (player->IsBust())
			{
				std::cout << "�~ �o�X�g!" << std::endl;
				break;
			}
		}
		player->Show(main_player);
	}

	// ���U���g
	std::cout << "--> ���ʔ��\" << std::endl;
	dealer_player->Show(dealer_player);
	for (auto& player : players)
	{
		if (player == dealer_player)
			continue;
		player->Show(player);
		std::cout << player->GetName() << ": ";
		if (player->IsBust() || player->GetTotal() < dealer_player->GetTotal())
			std::cout << "����";
		else
			std::cout << "����";
		std::cout << std::endl;
	}

	std::cout << "####### �u���b�N�W���b�N����� #######" << std::endl;
}