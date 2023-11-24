#pragma once

#include <atomic>

struct Pollable {

	Pollable();

	struct PollerRef {
		PollerRef(Pollable& pollable);
		~PollerRef();

		Pollable& mPollable;
	};

	PollerRef CreateRef();
	bool TryHold();

	operator bool();

	std::atomic_bool mPolling;
	std::atomic<size_t> mPollsFinished;
};

