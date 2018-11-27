#include "Player.h"
#include "Card.h"
#include "Game.h"

int Player::GetTotal()
{
	std::vector<std::unique_ptr<Card>&> pending;
	int total = 0;
	for (auto& card : m_cards)
	{
		int point = card->GetPoint();
		if (point < 0)
			pending.push_back(card);
		else
			total += point;
	}
	int i = pending.size();
	for (auto& card : pending)
	{
		if (total + 11 > Game::BUST_POINT && --i <= 0)
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
