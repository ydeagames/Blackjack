#pragma once

class Card;

class Deck
{
private:
	std::vector<std::unique_ptr<Card>> cards;

public:
	Deck();
	~Deck();

public:
	// ����
	void Create();
	// �V���b�t��
	void Shuffle();
	// �\��
	void Show();
	// �J�[�h������
	std::unique_ptr<Card> DrawCard();
};

