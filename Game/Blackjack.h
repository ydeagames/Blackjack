#pragma once

class User;

class Blackjack
{
public:
	// �o�X�g�̃|�C���g
	static const int BUST_POINT = 21;

private:
	// �f�B�[���[
	std::shared_ptr<User> dealerUser;
	// ��ʃs�[�|�[
	std::vector<std::shared_ptr<User>> playerUsers;

public:
	Blackjack(const std::shared_ptr<User>& dealerUser, const std::vector<std::shared_ptr<User>>& playerUsers)
		: dealerUser(dealerUser)
		, playerUsers(playerUsers) {}

public:
	// �����J�n
	int Start();
};
