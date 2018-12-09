#pragma once

class Card;

class Deck
{
private:
	std::vector<std::unique_ptr<Card>> m_cards;

public:
	Deck();
	~Deck();

public:
	// 生成
	void Create();
	// シャッフル
	void Shuffle();
	// 表示
	void Show();
	// カードを引く
	std::unique_ptr<Card> DrawCard();
};

