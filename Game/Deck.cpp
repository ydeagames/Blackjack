#include "Deck.h"
#include "Card.h"
#include "Utils.h"

Deck::Deck()
	: cards{}
{
}

Deck::~Deck()
{
}

// 生成
void Deck::Create()
{
	// クリア
	cards.clear();
	// 全カード生成
	for (int i = 0; i < Card::NUM_RANKS*Card::NUM_SUITS; i++)
		cards.emplace_back(std::make_unique<Card>(i));
}

// シャッフル
void Deck::Shuffle()
{
	// シャッフル・アルゴリズム
	int size = static_cast<int>(cards.size());
	for (int i = 0; i < size - 1; i++)
		utils::swap(cards[i], cards[utils::rndRange(i + 1, size - 1)]);
}

// 表示
void Deck::Show()
{
	bool start = true;
	for (auto& card : cards)
		if (card)
		{
			// 最初以外セミコロンを付ける
			if (start)
				start = false;
			else
				std::cout << ", ";
			// 表示
			card->Show(nullptr);
		}
	std::cout << std::endl;
}

// カードを引く
std::unique_ptr<Card> Deck::DrawCard()
{
	// カードを山札から消してから
	for (auto itr = cards.erase(cards.begin()); itr != cards.end(); itr = cards.erase(itr))
		if (*itr)
		{
			// オーナーをリセットして
			(*itr)->SetOwner(nullptr);
			// ムーブ
			return std::move(*itr);
		}
	throw std::logic_error("山札がありません");
}
