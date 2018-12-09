#pragma once

class User
{
private:
	std::string name;	// ���O
	int chip_before;	// �O��̃`�b�v
	int chip;			// �`�b�v

public:
	User(const std::string& name, int balance = 100)
		: name(name)
		, chip(balance)
		, chip_before(balance) {}
	~User() = default;

public:
	// �\��
	friend std::ostream& operator<<(std::ostream& os, const User& user);

public:
	// ���O�擾
	std::string GetName();

	// �`�b�v�ǉ�
	void AddChip(int score);
	// �`�b�v�Z�b�g
	void SetChip(int score);
	// �`�b�v���擾
	int GetChip();
	// �`�b�v��\��
	void ShowChip(bool show_before = true);
	// �R�~�b�g
	void Commit();
	// �O��̎����̃`�b�v
	int GetChipBefore();
};
