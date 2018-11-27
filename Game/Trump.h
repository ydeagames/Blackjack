#pragma once

class Card;

class Trump
{
private:
	std::vector<std::unique_ptr<Card>> m_cards;

public:
	Trump();
	~Trump();

public:
	void Create();
	void Shuffle();
	void Show();
	std::unique_ptr<Card> DrawCard();
};

