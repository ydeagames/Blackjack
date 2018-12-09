#pragma once

class Player;

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
	std::weak_ptr<Player> owner; // ���L��
	bool hidden;	// ��������

public:
	Card(int suit, int rank);
	Card(int id);
	~Card() = default;

public:
	void SetOwner(const std::shared_ptr<Player>& owner);		// ���L�҂��Z�b�g
	bool IsOwner(const std::shared_ptr<Player>& player);		// ���L�҂�
	void SetPrivate(bool hidden);								// �\�����ɂ��邩
	bool IsHidden();											// ��������
	bool IsVisible(const std::shared_ptr<Player>& player);		// ���邱�Ƃ��ł��邩

	void Show(const std::shared_ptr<Player>& player);			// ������̕\��
	int GetPoint(const std::shared_ptr<Player>& player);		// �|�C���g(�J�[�h�̉��l)���擾
};

