#include "Card.h"
#include "Player.h"

//const std::string Card::suits[] = { "\u2664", "\u2667", "\u2662", "\u2661" };
// �X�[�g
const std::string Card::suits[] = { "S", "C", "D", "H" };
// �����N
const std::string Card::ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

Card::Card(int suit, int rank)
	: suit(suit)
	, rank(rank)
	, hidden(false)
{
}

Card::Card(int id)
	: Card(id / Card::NUM_RANKS, id % Card::NUM_RANKS)
{
}

// �v���C���[���猩���J�[�h�\��
void Card::Show(const std::shared_ptr<Player>& player)
{
	// �����Ȃ�������?�\��
	if (!IsVisible(player))
		std::cout << "?";
	else
		std::cout << suits[suit] << ranks[rank];
}

// �|�C���g��Ԃ�
int Card::GetPoint(const std::shared_ptr<Player>& player)
{
	if (!IsVisible(player))
		return 0;
	if (rank >= 10)		// J Q K ��10�|�C���g
		return 10;
	else if (rank == 0)	// A ��1��11�|�C���g
		return -1;		// ���肳��Ă��Ȃ�
	return rank + 1;
}

// �I�[�i�[��ݒ�
void Card::SetOwner(const std::shared_ptr<Player>& _owner)
{
	owner = _owner;
}

// �I�[�i�[�m�F
bool Card::IsOwner(const std::shared_ptr<Player>& player)
{
	// nullptr�������猩����(���C���h�J�[�h)
	if (!player)
		return true;
	auto ownerptr = owner.lock();
	// ��ǃJ�[�h�������猩����
	if (!ownerptr)
		return true;
	return player->GetUser() == ownerptr->GetUser();
}

// ���Ԃ�
void Card::SetHidden(bool _hidden)
{
	hidden = _hidden;
}

// ���Ԃ���
bool Card::IsHidden()
{
	return hidden;
}

// �v���C���[�ɂƂ��Č����邩
bool Card::IsVisible(const std::shared_ptr<Player>& player)
{
	return !IsHidden() || IsOwner(player);
}
