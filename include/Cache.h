#pragma once

#include <deque>

template<typename T>
class Cache {

public:
	std::deque<T> mCache;
	size_t mMaxElems = 1;

	void setMaxElements(size_t newLimit)
	{
		mMaxElems = newLimit;
	}

	void Push(const T& obj)
	{
		while (mCache.size() >= 0 && mCache.size() + 1 >= mMaxElems)
			mCache.pop_back();

		mCache.push_front(obj);
	}

	void Reset()
	{
		mCache.clear();
	}
};