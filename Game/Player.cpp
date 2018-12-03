#include "Player.h"
#include "Card.h"
#include "Game.h"

void Player::Show(const std::unique_ptr<Player>& player)
{
	//bool start = true;
	//for (auto& card : m_cards)
	//	if (card)
	//	{
	//		if (start)
	//			start = false;
	//		else
	//			std::cout << ", ";
	//		if (this == player.get())
	//			card->ShowPrivate();
	//		else
	//			card->ShowPublic();
	//	}
	//std::cout << std::endl;
}

int Player::GetTotal()
{
	int num_pending = 0;
	int total = 0;
	for (auto& card : m_cards)
	{
		int point = card->GetPoint();
		if (point < 0)
			num_pending++;
		else
			total += point;
	}
	for (; num_pending > 0; num_pending--)
	{
		if (total + 11 > Game::BUST_POINT && num_pending <= 1)
			total += 11;
		else
			total += 1;
	}
	return total;
}

void Player::AddCard(std::unique_ptr<Card>&& newcard)
{
	m_cards.push_back(std::move(newcard));
}

std::string DealerPlayer::GetName()
{
	return "ディーラー";
}

bool DealerPlayer::ChooseHit()
{
	return GetTotal() <= 16;
}

bool DealerPlayer::IsDealer()
{
	return true;
}

std::string NormalPlayer::GetName()
{
	return name;
}

bool NormalPlayer::ChooseHit()
{
	std::cout << "ヒットしますか？ [y/n]> ";
	while (true)
	{
		char input = static_cast<char>(_getch());
		if (input == 'y' || input == 'Y')
		{
			std::cout << "はい" << std::endl;
			return true;
		}
		else if (input == 'n' || input == 'N')
		{
			std::cout << "いいえ" << std::endl;
			return false;
		}
	}
}

bool NormalPlayer::IsDealer()
{
	return false;
}
