#include <Pollable.h>

Pollable::Pollable()
	: mPolling(false)
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