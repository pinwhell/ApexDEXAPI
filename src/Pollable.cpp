#include <Pollable.h>

Pollable::Pollable(bool waitFirstPoll)
	: mPolling(false)
	, mbWaitFirstPoll(waitFirstPoll)
{}

Pollable::PollerRef::PollerRef(Pollable& pollable)
	: mPollable(pollable)
{}

Pollable::PollerRef::~PollerRef()
{
	mPollable.mPolling = false;
	mPollable.mPollsFinished++;
}

Pollable::operator bool()
{
	return mPolling;
}

Pollable::PollerRef Pollable::CreateRef()
{
	return PollerRef(*this);
}

bool Pollable::TryHold()
{
	return mPolling.exchange(true) == false;
}

bool Pollable::IsPreInitialPooling()
{
	return mPollsFinished == 0;
}

bool Pollable::IsPostInitialPooling()
{
	return mPollsFinished == 1;
}

bool Pollable::IsInitialPolling()
{
	return IsPreInitialPooling() || IsPostInitialPooling();
}

void Pollable::ManagePollerThread(std::thread& t)
{
	if (mbWaitFirstPoll && IsPreInitialPooling())
	{
		// At this point we are managing the first polling event
		// becouse of reason to initialize chaces etc, we wont simply 
		// detach from the first poll, since the first poll serves as a initial cache
		// that must be there thats why we gonna join the first polling

		if (t.joinable())
			t.join();

		return;
	}

	t.detach();
}
