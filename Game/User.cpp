#include "User.h"

std::ostream& operator<<(std::ostream& os, const User& user)
{
	return os << user.name;
}

std::string User::GetName()
{
	return name;
}

void User::AddChip(int score)
{
	chip += score;
}

void User::SetChip(int score)
{
	chip = score;
}

int User::GetChip()
{
	return chip;
}

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

void User::Commit()
{
	chip_before = chip;
}

int User::GetChipBefore()
{
	return chip_before;
}
