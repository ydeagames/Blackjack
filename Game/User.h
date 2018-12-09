#pragma once

class User
{
private:
	std::string name;	// 名前
	int chip_before;	// 前回のチップ
	int chip;			// チップ

public:
	User(const std::string& name, int balance = 100)
		: name(name)
		, chip(balance)
		, chip_before(balance) {}
	~User() = default;

public:
	// 表示
	friend std::ostream& operator<<(std::ostream& os, const User& user);

public:
	// 名前取得
	std::string GetName();

	// チップ追加
	void AddChip(int score);
	// チップセット
	void SetChip(int score);
	// チップを取得
	int GetChip();
	// チップを表示
	void ShowChip(bool show_before = true);
	// コミット
	void Commit();
	// 前回の試合のチップ
	int GetChipBefore();
};
