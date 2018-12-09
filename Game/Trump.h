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
	// ����
	void Create();
	// �V���b�t��
	void Shuffle();
	// �\��
	void Show();
	// �J�[�h������
	std::unique_ptr<Card> DrawCard();
};

