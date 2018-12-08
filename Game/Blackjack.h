#pragma once

class User;

class Blackjack
{
public:
	static const int BUST_POINT = 21;

public:
	void Start(const std::shared_ptr<User>& dealerUser, const std::vector<std::shared_ptr<User>>& playerUsers);
};
