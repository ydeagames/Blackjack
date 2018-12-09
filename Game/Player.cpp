#include "Player.h"
#include "Card.h"
#include "User.h"
#include "Blackjack.h"

// �����Ă�J�[�h����\��
void Player::Show(const std::shared_ptr<Player>& player, int draw_num)
{
	// A���܂ޏꍇ�̍ŏ����
	int total_min = GetPoint(player, true);
	// A���܂ޏꍇ�̍ő���
	int total = GetPoint(player);
	// ?���܂܂Ȃ��{���̐�
	int total_real = GetPoint(nullptr);
	std::cout << GetUser()->GetName() << "�̎�D(";
	// A������Ό��\��
	if (total_min != total)
		std::cout << total - 10 << "/";
	std::cout << total;
	// ?�������+?�\��
	if (total != total_real)
		std::cout << "+?";
	std::cout << "pt";

	// ��ԕ\��
	bool bust = IsBust();
	bool blackjack = IsBlackjack();
	if (bust)
		std::cout << "[BUST]";
	if (blackjack)
		std::cout << "[BLACKJACK]";
	std::cout << "): ";

	// �J�[�h���
	bool start = true;
	int i = static_cast<int>(cards.size());
	for (auto& card : cards)
		if (card)
		{
			// �ŏ��ȊO�Z�~�R������t����
			if (start)
				start = false;
			else
				std::cout << ", ";
			if (i <= draw_num)
			{
				PlaySound(TEXT("Resources/Audio/card_send.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
			}
			card->Show((bust || blackjack) ? nullptr : player);
			if (i <= draw_num)
				Sleep(400);
			i--;
		}
	std::cout << std::endl;
}

// �����J�[�h���v�̋���
int Player::GetPoint(const std::shared_ptr<Player>& owner, bool min_flag)
{
	int num_pending = 0;
	int total = 0;
	for (auto& card : cards)
	{
		// ������J�[�h�̒���
		if (card->IsVisible(owner))
		{
			int point = card->GetPoint(nullptr);
			// A�͕ۗ�
			if (point < 0)
				num_pending++;
			else
				total += point;
		}
	}

	if (num_pending > 0) // A��1���ȏゾ������
	{
		if (num_pending > 1)  // A��2���ȏゾ������
		{
			total += num_pending - 1; // 1���c���Ă��ׂĂ�A��1�Ƃ��Ēǉ�
			//num_pending = 1;  // A�͎c��1��
		}
		// A��11�ƈ����Ă�������BUST���Ȃ����Ȃ�11�Ƃ��Ĉ���
		if (total > 10 || min_flag)
			total += 1;
		else
			total += 11;
	}

	return total;
}

// �J�[�h�������Ă��邩
bool Player::HasCard(const std::shared_ptr<Player>& player, int point)
{
	for (auto& card : cards)
		if (card->GetPoint(player) == point)
			return true;
	return false;
}

// �o�X�g���Ă��邩
bool Player::IsBust()
{
	return GetPoint(nullptr) > Blackjack::BUST_POINT;
}

// �u���b�N�W���b�N��
bool Player::IsBlackjack()
{
	return GetPoint(nullptr) == Blackjack::BUST_POINT;
}

// BET���z�ݒ�
void Player::SetBet(int chip)
{
	bet = chip;
}

// BET���z�ǉ�
void Player::AddBet(int chip)
{
	bet += chip;
}

// BET����
void Player::Bet(int chip)
{
	auto user = GetUser();
	user->AddChip(-chip);
	AddBet(chip);
}

// BET���z�擾
int Player::GetBet()
{
	return bet;
}

// ���[�U�[�擾
std::shared_ptr<User> Player::GetUser()
{
	return user;
}

// �J�[�h��ǉ�
void Player::AddCard(std::unique_ptr<Card>&& newcard)
{
	// �I�[�i�[���Z�b�g
	newcard->SetOwner(shared_from_this());
	// �J�[�h���ړ�
	cards.push_back(std::move(newcard));
}

// �f�B�[���[��AI
Choice DealerPlayer::Choose(const std::shared_ptr<Player>& dealerPlayer)
{
	// 16�ȉ���������HIT����
	if (GetPoint(nullptr) <= 16)
		return Choice::HIT;
	return Choice::STAND;
}

// �f�B�[���[���ǂ���
bool DealerPlayer::IsDealer()
{
	return true;
}

std::shared_ptr<Player> DealerPlayer::Split()
{
	throw std::logic_error("�f�B�[���[��Split�ł��܂���");
}

// ����
void DealerPlayer::OnWin()
{
}

// ��������
void DealerPlayer::OnDraw()
{
}

// ����
void DealerPlayer::OnLose()
{
}

// �v���C���[�̑I��
Choice NormalPlayer::Choose(const std::shared_ptr<Player>& dealerPlayer)
{
	// �u���b�N�W���b�N�Ȃ�STAND����
	if (IsBlackjack())
		return Choice::STAND;

	// �t���O
	bool flag_begin = cards.size() == 2;
	bool flag_enough = GetUser()->GetChip() >= GetBet();
	bool flag_double = flag_begin && flag_enough;
	bool flag_split = flag_begin && flag_enough && !splited && (cards.front()->GetPoint(nullptr) == cards.back()->GetPoint(nullptr));
	bool flag_insurance = flag_begin && !insuranced && dealerPlayer->HasCard(shared_from_this(), -1);

	// �I����
	struct Choose
	{
		char input;
		std::string name;
		Choice choice;
	};
	// �I�����ꗗ
	std::vector<Choose> chooses;

	// �I�����\��
	char input = '1';
	chooses.push_back({ input++, "STAND", Choice::STAND });
	chooses.push_back({ input++, "HIT", Choice::HIT });
	if (flag_double)
		chooses.push_back({ input++, "DOUBLE", Choice::DOUBLE });
	if (flag_split && !splited)
		chooses.push_back({ input++, "SPLIT", Choice::SPLIT });
	if (flag_insurance)
		chooses.push_back({ input++, "INSURANCE", Choice::INSURANCE });

	// ���\��
	std::cout << "    ";
	std::cout << GetUser()->GetName() << "�̓q��: (�`�b�v: " << GetUser()->GetChip() << ", BET: " << GetBet() << ")" << std::endl;
	std::cout << "    ";
	for (Choose choose : chooses)
		std::cout << "[" << choose.input << ": " << choose.name << "] ";
	std::cout << std::endl;
	std::cout << "    ";
	std::cout << "> ";

	// �I��
	while (true)
	{
		char input = static_cast<char>(_getch());
		for (Choose choose : chooses)
			// �I�����ɂ����return����
			if (input == choose.input)
			{
				std::cout << "[" << choose.input << ": " << choose.name << "]" << std::endl;
				return choose.choice;
			}
	}
}

// �f�B�[���[���ǂ���
bool NormalPlayer::IsDealer()
{
	return false;
}

// SPLIT
std::shared_ptr<Player> NormalPlayer::Split()
{
	// ����
	auto cloned = std::make_shared<NormalPlayer>(GetUser());
	// �J�[�h�𕪊�
	auto split = std::move(cards.back());
	cards.pop_back();
	// �I�[�i�[�����Z�b�g
	split->SetOwner(nullptr);
	// �J�[�h���N���[���ɒǉ�
	cloned->AddCard(std::move(split));
	cloned->splited = true;
	// �T�C�hBET
	cloned->SetBet(0);
	cloned->Bet(GetBet());
	// �t���O
	splited = true;
	return cloned;
}

// ����
void NormalPlayer::OnWin()
{
	// �u���b�N�W���b�N��2.5�{
	if (IsBlackjack())
		GetUser()->AddChip(bet * 5 / 2);
	// BET����2�{�ɂȂ��ċA���Ă���
	else
		GetUser()->AddChip(bet * 2);
}

// ��������
void NormalPlayer::OnDraw()
{
	// BET�����A���Ă���
	GetUser()->AddChip(bet);
}

// ����
void NormalPlayer::OnLose()
{
	// None
}
