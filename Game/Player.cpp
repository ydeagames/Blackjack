#include "Player.h"
#include "Card.h"
#include "User.h"
#include "Blackjack.h"

void Player::Show(const std::shared_ptr<Player>& player)
{
	int total = GetTotal(player);
	int total_real = GetTotal(nullptr);
	std::cout << GetUser() << "‚ÌŽèŽD(";
	if (total == total_real)
		std::cout << total;
	else
		std::cout << total << "+?";
	std::cout << "pt";
	bool bust = IsBust();
	if (bust)
		std::cout << "[Bust]";
	std::cout << "): ";
	bool start = true;
	for (auto& card : m_cards)
		if (card)
		{
			if (start)
				start = false;
			else
				std::cout << ", ";
			card->Show(bust ? nullptr : player);
		}
	std::cout << std::endl;
}

int Player::GetTotal(const std::shared_ptr<Player>& owner)
{
	int num_pending = 0;
	int total = 0;
	for (auto& card : m_cards)
	{
		int point = card->GetPoint(nullptr);
		if (point < 0)
			num_pending++;
		else
			total += point;
	}
	for (; num_pending > 0; num_pending--)
	{
		if (total + 11 > Blackjack::BUST_POINT || num_pending > 1)
			total += 1;
		else
			total += 11;
	}
	for (auto& card : m_cards)
		if (!card->IsVisible(owner))
			total -= card->GetPoint(nullptr);
	return total;
}

bool Player::IsBust()
{
	return GetTotal(nullptr) > Blackjack::BUST_POINT;
}

User& Player::GetUser()
{
	return *user;
}

void Player::AddCard(std::unique_ptr<Card>&& newcard)
{
	newcard->SetOwner(shared_from_this());
	m_cards.push_back(std::move(newcard));
}

bool DealerPlayer::ChooseHit()
{
	return GetTotal(nullptr) <= 16;
}

bool DealerPlayer::IsDealer()
{
	return true;
}

bool NormalPlayer::ChooseHit()
{
	std::cout << "ƒqƒbƒg‚µ‚Ü‚·‚©H [y/n]> ";
	while (true)
	{
		char input = static_cast<char>(_getch());
		if (input == 'y' || input == 'Y')
		{
			std::cout << "‚Í‚¢" << std::endl;
			return true;
		}
		else if (input == 'n' || input == 'N')
		{
			std::cout << "‚¢‚¢‚¦" << std::endl;
			return false;
		}
	}
}

bool NormalPlayer::IsDealer()
{
	return false;
}
