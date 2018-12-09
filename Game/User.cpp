#include "User.h"

// 表示
std::ostream& operator<<(std::ostream& os, const User& user)
{
	return os << user.name;
}

// 名前取得
std::string User::GetName()
{
	return name;
}

// チップ追加
void User::AddChip(int score)
{
	chip += score;
}

// チップセット
void User::SetChip(int score)
{
	chip = score;
}

// チップを取得
int User::GetChip()
{
	return chip;
}

// チップを表示
void User::ShowChip(bool show_before)
{
	std::cout << GetName() << "のチップ: ";
	if (show_before)
	{
		if (chip_before > 0)
			std::cout << chip_before;
		else
			std::cout << "なし";
		std::cout << "→";
	}
	if (chip > 0)
		std::cout << chip;
	else
		std::cout << "なし";
	if (show_before)
		std::cout << "(" << chip - chip_before << ")";
	std::cout << std::endl;
}

// コミット
void User::Commit()
{
	chip_before = chip;
}

// 前回の試合のチップ
int User::GetChipBefore()
{
	return chip_before;
}
