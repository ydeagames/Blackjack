#pragma once

class User;

class Blackjack
{
public:
	// バストのポイント
	static const int BUST_POINT = 21;

private:
	// ディーラー
	std::shared_ptr<User> dealerUser;
	// 一般ピーポー
	std::vector<std::shared_ptr<User>> playerUsers;

public:
	Blackjack(const std::shared_ptr<User>& dealerUser, const std::vector<std::shared_ptr<User>>& playerUsers)
		: dealerUser(dealerUser)
		, playerUsers(playerUsers) {}

public:
	// 試合開始
	int Start();
};
