#pragma once

#include <chrono>

class Scheduler {
public:
	template<typename T>
	Scheduler(T interval = T(0))
		: mInterval(std::chrono::duration_cast<std::chrono::milliseconds>(interval))
		, mLastExecutionTime(std::chrono::steady_clock::now() - mInterval)
	{}

	void PostExecuted();
	bool IsExecutionTime() const;
	void SetInterval(std::chrono::milliseconds interval);
	operator bool() const;

private:

	std::chrono::milliseconds mInterval;
	std::chrono::steady_clock::time_point mLastExecutionTime;
};