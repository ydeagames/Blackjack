#pragma once

class User;
class Card;

enum class Choice
{
	STAND,
	HIT,
	DOUBLE,
	SPLIT,
	INSURANCE,
};

class Player : public std::enable_shared_from_this<Player>
{
protected:
	std::shared_ptr<User> user;
	std::vector<std::unique_ptr<Card>> cards;
	int bet = 0;

public:
	bool splited = false;
	bool insuranced = false;

protected:
	Player(const std::shared_ptr<User>& user)
		: user(user) {}

public:
	virtual ~Player() = default;

public:
	virtual Choice Choose(const std::shared_ptr<Player>& dealerPlayer) = 0;
	virtual bool IsDealer() = 0;
	virtual std::shared_ptr<Player> Split() = 0;
	virtual void OnWin() = 0;
	virtual void OnDraw() = 0;
	virtual void OnLose() = 0;
	
public:
	std::shared_ptr<User> GetUser();
	void AddCard(std::unique_ptr<Card>&& newcard);
	void Show(const std::shared_ptr<Player>& player, int draw_num = 0);
	int GetPoint(const std::shared_ptr<Player>& owner, bool min_flag = false);
	bool HasCard(const std::shared_ptr<Player>& player, int point);
	bool IsBust();
	bool IsBlackjack();
	void SetBet(int chip);
	void AddBet(int chip);
	void Bet(int chip);
	int GetBet();
};

class DealerPlayer : public Player
{
public:
	DealerPlayer(const std::shared_ptr<User>& user)
		: Player(user) {}
	virtual ~DealerPlayer() = default;

public:
	virtual Choice Choose(const std::shared_ptr<Player>& dealerPlayer) override;
	virtual bool IsDealer() override;
	virtual std::shared_ptr<Player> Split() override;
	virtual void OnWin() override;
	virtual void OnDraw() override;
	virtual void OnLose() override;
};

class NormalPlayer : public Player
{
public:
	NormalPlayer(const std::shared_ptr<User>& user)
		: Player(user) {}
	virtual ~NormalPlayer() = default;

public:
	virtual Choice Choose(const std::shared_ptr<Player>& dealerPlayer) override;
	virtual bool IsDealer() override;
	virtual std::shared_ptr<Player> Split() override;
	virtual void OnWin() override;
	virtual void OnDraw() override;
	virtual void OnLose() override;
};