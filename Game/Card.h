#pragma once

class Card
{
public:
	static const int NUM_SUITS = 4;				// �X�[�g�̐�
	static const int NUM_RANKS = 13;			// �����N�̐�

public:
	static const std::string suits[NUM_SUITS];	// �X�[�g
	static const std::string ranks[NUM_RANKS];	// �����N

private:
	int suit;			// �}�[�N
	int rank;			// �����N
	bool is_private;	// ��������

public:
	Card(int suit, int rank);
	Card(int id);
	~Card() = default;

public:
	void ShowPublic();				// ��ʕ\��
	void ShowPrivate();				// ������̕\��
	int GetPoint();					// �|�C���g(�J�[�h�̉��l)���擾
	void SetPrivate(bool hidden);	// �\�����ɂ��邩
	bool IsPrivate();				// ��������
};

