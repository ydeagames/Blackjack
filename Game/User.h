#pragma once

class User
{
public:
	std::string name;
	int balance;

public:
	User(const std::string& name, int balance = 100)
		: name(name)
		, balance(balance) {}
	~User() = default;

	
};

