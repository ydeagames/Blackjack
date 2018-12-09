#include "Card.h"
#include "Player.h"

//const std::string Card::suits[] = { "\u2664", "\u2667", "\u2662", "\u2661" };
// スート
const std::string Card::suits[] = { "S", "C", "D", "H" };
// ランク
const std::string Card::ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

Card::Card(int suit, int rank)
	: suit(suit)
	, rank(rank)
	, hidden(false)
{
}

Card::Card(int id)
	: Card(id / Card::NUM_RANKS, id % Card::NUM_RANKS)
{
}

// プレイヤーから見たカード表示
void Card::Show(const std::shared_ptr<Player>& player)
{
	// 見えなかったら?表示
	if (!IsVisible(player))
		std::cout << "?";
	else
		std::cout << suits[suit] << ranks[rank];
}

// ポイントを返す
int Card::GetPoint(const std::shared_ptr<Player>& player)
{
	if (!IsVisible(player))
		return 0;
	if (rank >= 10)		// J Q K は10ポイント
		return 10;
	else if (rank == 0)	// A は1か11ポイント
		return -1;		// 決定されていない
	return rank + 1;
}

// オーナーを設定
void Card::SetOwner(const std::shared_ptr<Player>& _owner)
{
	owner = _owner;
}

// オーナー確認
bool Card::IsOwner(const std::shared_ptr<Player>& player)
{
	// nullptrだったら見せる(ワイルドカード)
	if (!player)
		return true;
	auto ownerptr = owner.lock();
	// 野良カードだったら見せる
	if (!ownerptr)
		return true;
	return player->GetUser() == ownerptr->GetUser();
}

// 裏返し
void Card::SetHidden(bool _hidden)
{
	hidden = _hidden;
}

// 裏返しか
bool Card::IsHidden()
{
	return hidden;
}

// プレイヤーにとって見えるか
bool Card::IsVisible(const std::shared_ptr<Player>& player)
{
	return !IsHidden() || IsOwner(player);
}
