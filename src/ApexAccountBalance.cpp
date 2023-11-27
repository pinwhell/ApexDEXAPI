#include <ApexAccountBalance.h>

ApexAccountBalance::ApexAccountBalance(const ApexPrivateAPIRequestBuilder& requestBuilder, BS::thread_pool_light& threadPool)
	: mRequestBuilder(requestBuilder)
	, mThreadPool(threadPool)
{}

void ApexAccountBalance::FetchData()
{
	if (!mPollable.TryHold())
		return;

	mThreadPool.push_task([this] {
		Pollable::PollerRef ref = mPollable;

		httplib::Result res = mRequestBuilder
			.Reset()
			.setMethod("GET")
			.setEndpoint("/account-balance")
			.Build()
			.Perform();

		if (!res)
			return;

		try {
			nlohmann::json accData = nlohmann::json::parse(res->body);
			accData = accData["data"];
			mQueue.Enqueue(accData);
		}
		catch (...) {}

		});
}

void ApexAccountBalance::ProcessData()
{
	mQueue.ProcessAll([this](const nlohmann::json& accData) {
		mTotalEquity = std::stod(accData["totalEquityValue"].get<std::string>());
		mAvailableBalance = std::stod(accData["availableBalance"].get<std::string>());
		});
}

double ApexAccountBalance::getTotalEquity()
{
	return mTotalEquity;
}

double ApexAccountBalance::getAvailableBalance()
{
	return mAvailableBalance;
}
