#pragma once

#include <atomic>
#include <thread>

struct Pollable {

	Pollable(bool waitFirstPoll);

	struct PollerRef {
		PollerRef(Pollable& pollable);
		~PollerRef();

		Pollable& mPollable;
	};

	PollerRef CreateRef();
	bool TryHold();
	bool IsPreInitialPooling();
	bool IsPostInitialPooling();
	bool IsInitialPolling();
	void ManagePollerThread(std::thread& t);

	operator bool();

	std::atomic_bool mPolling;
	std::atomic<size_t> mPollsFinished;
	bool mbWaitFirstPoll;
};

