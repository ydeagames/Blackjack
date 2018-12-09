#pragma once

class User
{
private:
	std::string name;
	int chip;

public:
	User(const std::string& name, int balance = 100)
		: name(name)
		, chip(balance) {}
	~User() = default;

public:
	friend std::ostream& operator<<(std::ostream& os, const User& user);

public:
	std::string GetName();

	void AddChip(int score);
	void SetChip(int score);
	int GetChip();
	void ShowChip();
};
