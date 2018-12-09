#include "Blackjack.h"
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "User.h"

int Blackjack::Start()
{
	Sleep(50);

	// ������
	Deck trump = {};	// �g�����v�P�[�X��p��
	trump.Create();		// �g�����v��p��
	trump.Shuffle();	// �g�����v���V���b�t��

	// ���[�U�[����Q�[���ɎQ������v���C���[���쐬
	std::vector<std::shared_ptr<Player>> players;
	for (auto& playerUser : playerUsers)
		players.emplace_back(std::make_shared<NormalPlayer>(playerUser));	// �ʏ�v���C���[
	players.emplace_back(std::make_shared<DealerPlayer>(dealerUser));		// �f�B�[���[�v���C���[

	// ��ʂ̑O�ɂ���l (�����̃J�[�h��?�ɂȂ�Ȃ�)
	auto main_player = players.front();
	// �f�B�[���[
	auto dealer_player = players.back();

	// BET����
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/card_drag.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> BET�ݒ�" << std::endl;
	Sleep(800);
	for (auto& player : players)
	{
		// �f�B�[���[�ł͂Ȃ��l�݂̂�BET�ł���
		if (!player->IsDealer())
		{
			while (true)
			{
				// �`�b�v
				int chip = player->GetUser()->GetChip();
				std::cout << "  <" << player->GetUser()->GetName() << "��BET�z>" << std::endl;
				std::cout << "    BET�z���w�肵�Ă������� [-1: �Q�[�����I��]" << std::endl;

				// �ʓrBET�����
				std::cout << "    > ";
				int bet;
				std::cin >> bet;

				// �`�b�v�m�F
				if (bet > chip)		// ����Ȃ�
					std::cout << "    <!> �`�b�v������܂���" << std::endl;
				else if (bet == 0)	// 0�`�b�v�q��
					std::cout << "    <!> 1�`�b�v�ȏォ����K�v������܂�" << std::endl;
				else if (bet < 0)	// �Q�[���I��
				{
					std::cout << "    (i) �Q�[�����I�����܂�" << std::endl;
					return -1;
				}
				else				// BET
				{
					std::cout << "    ";
					std::cout << chip << "��";
					// �q����
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

	// �J�[�h�z�z
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/card_kubaru.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> �J�[�h�z�z" << std::endl;
	Sleep(800);
	for (auto& player : players)
	{
		// �f�b�L����J�[�h������
		auto card = trump.DrawCard();
		// �f�B�[���[�̈ꖇ�ڂ͕�����
		if (player->IsDealer())
			card->SetHidden(true);
		// �z��
		player->AddCard(std::move(card));
		player->AddCard(trump.DrawCard());
		std::cout << "  ";
		// �\������
		player->Show(main_player, 2);
	}

	// �Q�[���J�n
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/button.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> �Q�[���J�n" << std::endl;
	Sleep(800);
	for (auto itr = players.begin(); itr != players.end(); ++itr)
	{
		std::shared_ptr<Player> player = *itr;

		std::cout << "  <" << player->GetUser()->GetName() << "�̃^�[��>" << std::endl;

		// �L���ȑI��������܂Ń��[�v
		bool choice_running = true;
		while (choice_running)
		{
			std::cout << "    ";
			// �\��
			player->Show(nullptr);
			// �I��
			Choice choicehit = player->Choose(dealer_player);

			// �f�b�L����ꖇ�J�[�h�������֐�
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
			// �������A�N�V����
			switch (choicehit)
			{
			case Choice::STAND:
				std::cout << "STAND��I�т܂���";
				choice_running = false;
				break;
			case Choice::HIT:
				std::cout << "HIT��I�т܂���";
				draw_func(player);
				break;
			case Choice::DOUBLE:
				std::cout << "DOUBLE��I�т܂���";
				draw_func(player);
				// �q����2�{�ɂ��� = ���̓q�������q����
				player->Bet(player->GetBet());
				choice_running = false;
				break;
			case Choice::SPLIT:
				std::cout << "SPLIT��I�т܂���";
				// �����v���C���[������Ă��̃v���C���[�̂��Ƃɑ}������
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
				std::cout << "INSURANCE��I�т܂���";
				// �q����1/2�ɂ���
				player->Bet(-player->GetBet() / 2);
				player->insuranced = true;
				break;
			}
			Sleep(800);
			std::cout << std::endl;
			// �o�X�g
			if (player->IsBust())
			{
				std::cout << "    ";
				PlaySound(TEXT("Resources/Audio/button_cancel.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				std::cout << "�~ BUST!" << std::endl;
				Sleep(800);
				break;
			}
		}
		std::cout << "    ";
		// ���C���v���C���[�ɕ\���ł�����̂�\��
		player->Show(main_player);
		std::cout << std::endl;
		Sleep(1000);
	}

	// ���U���g
	//std::cout << std::endl;
	std::cout << "--> ���ʔ��\" << std::endl;
	PlaySound(TEXT("Resources/Audio/card_mekuru.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "  ";
	// �f�B�[���[�̕����J�[�h���܂ߌ��ʕ\��
	dealer_player->Show(nullptr);
	Sleep(800);
	for (auto& player : players)
	{
		if (player == dealer_player)
			continue;
		std::cout << "  <" << player->GetUser()->GetName() << "�̌���>" << std::endl;
		std::cout << "    ";
		// �v���C���[�̃J�[�h�Ċm�F
		player->Show(player);
		std::cout << "    ";
		std::cout << player->GetUser()->GetName() << "�̏��s: ";
		int sub;
		// �f�B�[���[�̃u���b�N�W���b�N�A�v���C���[�̃o�X�g�̓v���C���[�̕���
		if (dealer_player->IsBlackjack() || player->IsBust())
			sub = -1;
		// �����łȂ��ꍇ�A�f�B�[���[�̃o�X�g�͏���
		else if (dealer_player->IsBust())
			sub = 1;
		else
			sub = player->GetPoint(nullptr) - dealer_player->GetPoint(nullptr);
		if (sub < 0)
		{
			PlaySound(TEXT("Resources/Audio/fail.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(200);
			std::cout << "����";
			Sleep(800);
			player->OnLose();
		}
		else if (sub == 0)
		{
			Sleep(200);
			std::cout << "��������";
			Sleep(800);
			player->OnDraw();
		}
		else
		{
			// �u���b�N�W���b�N
			if (player->IsBlackjack())
			{
				PlaySound(TEXT("Resources/Audio/cheer.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				std::cout << "����(BLACKJACK)";
				Sleep(1600);
			}
			else
			{
				PlaySound(TEXT("Resources/Audio/success.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
				std::cout << "����";
				Sleep(800);
			}
			player->OnWin();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
