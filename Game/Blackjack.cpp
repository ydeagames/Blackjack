#include "Blackjack.h"
#include "Trump.h"
#include "Player.h"
#include "Card.h"
#include "User.h"

void Blackjack::Start()
{
	std::cout << "########## �u���b�N�W���b�N ##########" << std::endl;

	// ������
	Trump trump = {};	// �g�����v�P�[�X��p��
	trump.Create();		// �g�����v��p��
	trump.Shuffle();	// �g�����v���V���b�t��

	std::vector<std::shared_ptr<Player>> players;
	for (auto& playerUser : playerUsers)
		players.emplace_back(std::make_shared<NormalPlayer>(playerUser));
	players.emplace_back(std::make_shared<DealerPlayer>(dealerUser));
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

	std::vector<std::shared_ptr<Player>> done_players;

	// �Q�[���J�n
	std::cout << "--> �Q�[���J�n" << std::endl;
	for (auto itr = players.begin(); itr == players.end(); ++itr)
	{
		std::shared_ptr<Player>& player = *itr;

		std::cout << "! " << player->GetUser() << "�̃^�[��" << std::endl;
		bool choice_running = true;
		while (choice_running)
		{
			player->Show(main_player);
			Choice choicehit = player->Choose(dealer_player);
			switch (choicehit)
			{
			case Choice::STAND:
				std::cout << "@ �X�^���h" << std::endl;
				choice_running = false;
				break;
			case Choice::HIT:
				std::cout << "@ �q�b�g!";
				{
					auto card = trump.DrawCard();
					std::cout << "(Get: ";
					card->Show(main_player);
					std::cout << ")" << std::endl;
					player->AddCard(std::move(card));
				}
				break;
			case Choice::DOUBLE:
				break;
			case Choice::SPLIT:
				std::cout << "@ �X�v���b�g" << std::endl;
				break;
			case Choice::INSURANCE:
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
		std::cout << player->GetUser() << ": ";
		if (player->IsBust() || player->GetPoint(nullptr) < dealer_player->GetPoint(nullptr))
			std::cout << "����";
		else
			std::cout << "����";
		std::cout << std::endl;
	}

	std::cout << "####### �u���b�N�W���b�N����� #######" << std::endl;
}
