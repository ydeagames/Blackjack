#include "User.h"

// �\��
std::ostream& operator<<(std::ostream& os, const User& user)
{
	return os << user.name;
}

// ���O�擾
std::string User::GetName()
{
	return name;
}

// �`�b�v�ǉ�
void User::AddChip(int score)
{
	chip += score;
}

// �`�b�v�Z�b�g
void User::SetChip(int score)
{
	chip = score;
}

// �`�b�v���擾
int User::GetChip()
{
	return chip;
}

// �`�b�v��\��
void User::ShowChip(bool show_before)
{
	std::cout << GetName() << "�̃`�b�v: ";
	if (show_before)
	{
		if (chip_before > 0)
			std::cout << chip_before;
		else
			std::cout << "�Ȃ�";
		std::cout << "��";
	}
	if (chip > 0)
		std::cout << chip;
	else
		std::cout << "�Ȃ�";
	if (show_before)
		std::cout << "(" << chip - chip_before << ")";
	std::cout << std::endl;
}

// �R�~�b�g
void User::Commit()
{
	chip_before = chip;
}

// �O��̎����̃`�b�v
int User::GetChipBefore()
{
	return chip_before;
}
