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

void User::ShowChip()
{
	std::cout << GetName() << "‚Ìƒ`ƒbƒv: ";
	if (chip > 0)
		std::cout << chip << std::endl;
	else
		std::cout << "‚È‚µ" << std::endl;
}
