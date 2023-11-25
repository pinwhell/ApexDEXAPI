#include <taskschd.h>
#include "Scheduler.h"

bool Scheduler::IsExecutionTime() const {
	auto currentTime = std::chrono::steady_clock::now();
	return (currentTime - mLastExecutionTime) >= mInterval;
}

void Scheduler::SetInterval(std::chrono::milliseconds interval) {
	mInterval = interval;
}

Scheduler::operator bool() const
{
	return IsExecutionTime();
}

void Scheduler::PostExecuted() {
	mLastExecutionTime = std::chrono::steady_clock::now();
}
