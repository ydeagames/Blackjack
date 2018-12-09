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
		m_cards.emplace_back(std::make_unique<Card>(i));
}

void Trump::Shuffle()
{
	int size = static_cast<int>(m_cards.size());
	for (int i = 0; i < size - 1; i++)
		utils::swap(m_cards[i], m_cards[utils::rndRange(i + 1, size - 1)]);
}

void Trump::Show()
{
	bool start = true;
	for (auto& card : m_cards)
		if (card)
		{
			if (start)
				start = false;
			else
				std::cout << ", ";
			card->Show(nullptr);
		}
	std::cout << std::endl;
}

std::unique_ptr<Card> Trump::DrawCard()
{
	for (auto itr = m_cards.erase(m_cards.begin()); itr != m_cards.end(); itr = m_cards.erase(itr))
		if (*itr)
		{
			(*itr)->SetOwner(nullptr);
			return std::move(*itr);
		}
	throw std::logic_error("ŽRŽD‚ª‚ ‚è‚Ü‚¹‚ñ");
}
