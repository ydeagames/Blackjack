#include "Game.h"
#include "Blackjack.h"
#include "User.h"

void Game::Start()
{
	std::cout << "�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��" << std::endl;
	std::cout << "��                                               ��" << std::endl;
	std::cout << "��               B L A C K J A C K               ��" << std::endl;
	std::cout << "��                                               ��" << std::endl;
	std::cout << "�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��" << std::endl;
	std::cout << "��                               (c) YdeaGames   ��" << std::endl;
	std::cout << "�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��" << std::endl;

	// �����`�b�v
	int default_balance = 1000;

	// �f�B�[���[
	std::shared_ptr<User> dealer = std::make_shared<User>("�f�B�[���[", default_balance);

	// �v���C���[
	std::shared_ptr<User> player = std::make_shared<User>("���Ȃ�", default_balance);
	std::vector<std::shared_ptr<User>> players = { player };

	std::cout << std::endl;
	std::cout << "--> �����`�b�v" << std::endl;
	// ��������
	for (auto& player : players)
	{
		std::cout << "  ";
		player->ShowChip(false);
	}

	// �Q�[�����[�v
	bool running = true;
	while (running)
	{
		// ������������
		Blackjack blackjack = { dealer, players };
		// �����J�n
		bool is_exit = blackjack.Start() == -1;

		if (is_exit)
			running = false;
		else
			// ����
			for (auto& player : players)
			{
				// ���ʂ�\��
				player->ShowChip();
				// ���ʂɃR�~�b�g
				player->Commit();
				// �L����S���n��������I��
				if (player->GetChip() <= 0)
					running = false;
			}
	}

	// �ŏI����
	std::cout << std::endl;
	PlaySound(TEXT("Resources/Audio/button_cancel.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	std::cout << "--> �ŏI����" << std::endl;
	Sleep(800);
	for (auto& player : players)
	{
		std::cout << "  ";
		player->ShowChip(false);
	}
}
