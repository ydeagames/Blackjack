#pragma once

class User;

class Blackjack
{
public:
	static const int BUST_POINT = 21;

private:
	std::shared_ptr<User> dealerUser;
	std::vector<std::shared_ptr<User>> playerUsers;

public:
	Blackjack(const std::shared_ptr<User>& dealerUser, const std::vector<std::shared_ptr<User>>& playerUsers)
		: dealerUser(dealerUser)
		, playerUsers(playerUsers) {}

public:
	int Start();
};
