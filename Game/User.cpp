#include "User.h"

std::ostream& operator<<(std::ostream& os, const User& user)
{
	return os << user.name;
}

void User::AddScore(int score)
{
	balance += score;
}
