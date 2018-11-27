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
	virtual int GetTotal();
	virtual void AddCard(std::unique_ptr<Card>&& newcard);
};

class DealerPlayer : public Player
{
public:
	DealerPlayer() = default;
	virtual ~DealerPlayer() = default;

public:
	std::string GetName() override;
	bool ChooseHit() override;
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
};