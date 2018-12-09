#include "Card.h"

//const std::string Card::suits[] = { "\u2664", "\u2667", "\u2662", "\u2661" };
const std::string Card::suits[] = { "S", "C", "D", "H" };
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

void Card::Show(const std::shared_ptr<Player>& player)
{
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

void Card::SetOwner(const std::shared_ptr<Player>& _owner)
{
	owner = _owner;
}

bool Card::IsOwner(const std::shared_ptr<Player>& player)
{
	if (!player)
		return true;
	auto ownerptr = owner.lock();
	if (!ownerptr)
		return true;
	return player == ownerptr;
}

void Card::SetPrivate(bool _hidden)
{
	hidden = _hidden;
}

bool Card::IsHidden()
{
	return hidden;
}

bool Card::IsVisible(const std::shared_ptr<Player>& player)
{
	return !IsHidden() || IsOwner(player);
}
