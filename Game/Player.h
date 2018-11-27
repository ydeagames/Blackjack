#pragma once

class Card;

class Player
{
protected:
	std::vector<std::unique_ptr<Card>> m_cards;

public:
	Player() = default;
	virtual ~Player() = default;

public:
	virtual std::string GetName() = 0;
	virtual bool ChooseHit() = 0;
	virtual bool IsDealer() = 0;
	virtual void AddCard(std::unique_ptr<Card>&& newcard);
	virtual void Show(const std::unique_ptr<Player>& player);
	virtual int GetTotal();
};

class DealerPlayer : public Player
{
public:
	DealerPlayer() = default;
	virtual ~DealerPlayer() = default;

public:
	std::string GetName() override;
	bool ChooseHit() override;
	bool IsDealer() override;
};

class NormalPlayer : public Player
{
private:
	std::string name;

public:
	NormalPlayer(const std::string& name)
		: name(name) {}
	virtual ~NormalPlayer() = default;

public:
	std::string GetName() override;
	bool ChooseHit() override;
	bool IsDealer() override;
};