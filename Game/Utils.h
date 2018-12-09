#pragma once

// ���[�e�B���e�B
namespace utils
{
	// ���[�v
	inline int loop(int x, int max)
	{
		return ((x % max) + max) % max;
	}

	// �͈̓��[�v
	inline int loopRange(int x, int min, int max)
	{
		return ((x % max) + max) % max;
	}

	// �����_��
	inline int rnd(int max)
	{
		return std::rand() % (max + 1);
	}

	// �͈̓����_��
	inline int rndRange(int min, int max)
	{
		return rnd(max - min) + min;
	}

	// �X���b�v�֐� (std::swap�Ɠ���)
	template<class t>
	void swap(t& a, t& b)
	{
		//std::swap(a, b);
		t tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
	}
}
