#include "Card.h"

//const std::string Card::suits[] = { "\u2664", "\u2667", "\u2662", "\u2661" };
const std::string Card::suits[] = { "S", "C", "D", "H" };
const std::string Card::ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

Card::Card(int suit, int rank)
	: suit(suit)
	, rank(rank)
	, is_private(false)
{
}

Card::Card(int id)
	: Card(id / Card::NUM_RANKS, id % Card::NUM_RANKS)
{
}

void Card::ShowPublic()
{
	if (is_private)
		std::cout << "?";
	else
		std::cout << suits[suit] << ranks[rank];
}

void Card::ShowPrivate()
{
	std::cout << suits[suit] << ranks[rank];
}

// �|�C���g��Ԃ�
int Card::GetPoint()
{
	if (rank >= 10)		// J Q K ��10�|�C���g
		return 10;
	else if (rank == 0)	// A ��1��11�|�C���g
		return -1;		// ���肳��Ă��Ȃ�
	return rank + 1;
}

void Card::SetPrivate(bool hidden)
{
	is_private = hidden;
}

bool Card::IsPrivate()
{
	return is_private;
}
