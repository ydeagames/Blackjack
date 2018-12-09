#pragma once

class Player;

class Card
{
public:
	static const int NUM_SUITS = 4;				// スートの数
	static const int NUM_RANKS = 13;			// ランクの数

public:
	static const std::string suits[NUM_SUITS];	// スート
	static const std::string ranks[NUM_RANKS];	// ランク

private:
	int suit;			// マーク
	int rank;			// ランク
	std::weak_ptr<Player> owner; // 所有者
	bool hidden;	// 裏向きか

public:
	Card(int suit, int rank);
	Card(int id);
	~Card() = default;

public:
	void SetOwner(const std::shared_ptr<Player>& owner);		// 所有者をセット
	bool IsOwner(const std::shared_ptr<Player>& player);		// 所有者か
	void SetPrivate(bool hidden);								// 表向きにするか
	bool IsHidden();											// 裏向きか
	bool IsVisible(const std::shared_ptr<Player>& player);		// 見ることができるか

	void Show(const std::shared_ptr<Player>& player);			// 持ち主の表示
	int GetPoint(const std::shared_ptr<Player>& player);		// ポイント(カードの価値)を取得
};

