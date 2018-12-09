#include "Deck.h"
#include "Card.h"
#include "Utils.h"

Deck::Deck()
	: m_cards{}
{
}

Deck::~Deck()
{
}

// ����
void Deck::Create()
{
	// �N���A
	m_cards.clear();
	// �S�J�[�h����
	for (int i = 0; i < Card::NUM_RANKS*Card::NUM_SUITS; i++)
		m_cards.emplace_back(std::make_unique<Card>(i));
}

// �V���b�t��
void Deck::Shuffle()
{
	// �V���b�t���E�A���S���Y��
	int size = static_cast<int>(m_cards.size());
	for (int i = 0; i < size - 1; i++)
		utils::swap(m_cards[i], m_cards[utils::rndRange(i + 1, size - 1)]);
}

// �\��
void Deck::Show()
{
	bool start = true;
	for (auto& card : m_cards)
		if (card)
		{
			// �ŏ��ȊO�Z�~�R������t����
			if (start)
				start = false;
			else
				std::cout << ", ";
			// �\��
			card->Show(nullptr);
		}
	std::cout << std::endl;
}

// �J�[�h������
std::unique_ptr<Card> Deck::DrawCard()
{
	// �J�[�h���R�D��������Ă���
	for (auto itr = m_cards.erase(m_cards.begin()); itr != m_cards.end(); itr = m_cards.erase(itr))
		if (*itr)
		{
			// �I�[�i�[�����Z�b�g����
			(*itr)->SetOwner(nullptr);
			// ���[�u
			return std::move(*itr);
		}
	throw std::logic_error("�R�D������܂���");
}
