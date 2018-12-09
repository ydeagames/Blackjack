#pragma once

// ユーティリティ
namespace utils
{
	// ループ
	inline int loop(int x, int max)
	{
		return ((x % max) + max) % max;
	}

	// 範囲ループ
	inline int loopRange(int x, int min, int max)
	{
		return ((x % max) + max) % max;
	}

	// ランダム
	inline int rnd(int max)
	{
		return std::rand() % (max + 1);
	}

	// 範囲ランダム
	inline int rndRange(int min, int max)
	{
		return rnd(max - min) + min;
	}

	// スワップ関数 (std::swapと同じ)
	template<class t>
	void swap(t& a, t& b)
	{
		//std::swap(a, b);
		t tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
	}
}
