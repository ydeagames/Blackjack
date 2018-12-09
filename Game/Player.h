#pragma once

class User;
class Card;

class Player : public std::enable_shared_from_this<Player>
{
protected:
	std::shared_ptr<User> user;
	std::vector<std::unique_ptr<Card>> m_cards;

private:
	Player(const std::shared_ptr<User>& user)
		: user(user) {}

public:
	virtual ~Player() = default;

public:
	virtual bool ChooseHit() = 0;
	virtual bool IsDealer() = 0;
	
public:
	User& GetUser();
	void AddCard(std::unique_ptr<Card>&& newcard);
	void Show(const std::shared_ptr<Player>& player);
	int GetTotal(const std::shared_ptr<Player>& owner);
	bool IsBust();
};

class DealerPlayer : public Player
{
public:
	DealerPlayer(const std::shared_ptr<User>& user)
		: Player(user) {}
	virtual ~DealerPlayer() = default;

public:
	bool ChooseHit() override;
	bool IsDealer() override;
};

class NormalPlayer : public Player
{
public:
	NormalPlayer(const std::shared_ptr<User>& user)
		: Player(user) {}
	virtual ~NormalPlayer() = default;

public:
	bool ChooseHit() override;
	bool IsDealer() override;
};