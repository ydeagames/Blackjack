#pragma once

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

public:
	Card(int suit, int rank);
	Card(int id);
	~Card() = default;

public:
	void ShowCard();				// 表示
	int GetPoint();					// ポイント(カードの価値)を取得
};

