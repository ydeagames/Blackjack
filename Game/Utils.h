#pragma once

namespace utils
{
	inline int loop(int x, int max)
	{
		return ((x % max) + max) % max;
	}

	inline int loopRange(int x, int min, int max)
	{
		return ((x % max) + max) % max;
	}

	inline int rnd(int max)
	{
		return std::rand() % (max + 1);
	}

	inline int rndRange(int min, int max)
	{
		return rnd(max - min) + min;
	}

	inline int rndRangeIgnore(int min, int max, int ignore)
	{
		int rnd = rndRange(min, max - 1);
		if (rnd >= ignore)
			rnd++;
		return rnd;
	}

	template<class t>
	void swap(t& a, t& b)
	{
		//std::swap(a, b);
		t tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
	}
}
