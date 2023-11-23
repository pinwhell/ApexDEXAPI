#pragma once

#include <queue>
#include <mutex>

template<typename T>
struct SafeQueue {
public:
	void Enqueue(const T& data)
	{
		std::lock_guard<std::mutex> lck(mLock);

		mQueue.push(data);
	}

	void ProcessAll(std::function<void(const T&)> callback)
	{
		if (mQueue.size() == 0)
			return;

		std::lock_guard<std::mutex> lck(mLock);

		while (mQueue.empty() == false)
		{
			const T& data = mQueue.front();

			callback(data);

			mQueue.pop();
		}
	}

private:
	std::queue<T> mQueue;
	std::mutex mLock;
};
