#include "Trump.h"
#include "Card.h"
#include "Utils.h"

Trump::Trump()
	: m_cards{}
{
}

Trump::~Trump()
{
}

void Trump::Create()
{
	m_cards.clear();
	for (int i = 0; i < Card::NUM_RANKS*Card::NUM_SUITS; i++)
		m_cards.push_back(std::make_shared<Card>(i));
}

void Trump::Shuffle()
{
	for (int i = 0; i < NUM_CARDS - 1; i++)
		utils::swap(m_cards[i], m_cards[utils::rndRange(i + 1, NUM_CARDS - 1)]);
}

void Trump::ShowTrump()
{
	bool start = true;
	for (auto& card : m_cards)
		if (card)
		{
			if (start)
				start = false;
			else
				std::cout << ", ";
			card->ShowCard();
		}
	std::cout << std::endl;
}

std::unique_ptr<Card> Trump::DrawCard()
{
	for (auto itr = m_cards.begin(); itr != m_cards.end(); itr = m_cards.erase(itr))
		if (*itr)
			return *itr;
	return nullptr;
}
