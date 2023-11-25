#include <ApexPriceHistory.h>

ApexPriceHistory::ApexPriceHistory(const ApexAPIRequestBuilder& requestBuilder, const CurrencyPair& currencyPair, size_t candleInterval, BS::thread_pool_light& threadPool)
	: mCurrencyPair(currencyPair)
	, mCandleInterval(candleInterval)
	, mRequestBuilder(requestBuilder)
	, mCandleList(50)
	, mThreadPool(threadPool)
{}

void ApexPriceHistory::ProcessData()
{
	mQueue.ProcessAll([this](const nlohmann::json& data) {
		mCandleList.Update(data);
		});
}

void ApexPriceHistory::AddOnTickCallback(std::function<void(const ApexCandleList&)> callback)
{
	mCandleList.AddOnTickCallback(callback);
}

void ApexPriceHistory::UpdateCheckTick()
{
	mCandleList.UpdateCheckTick();
}

ApexCandleList& ApexPriceHistory::getCandles()
{
	return mCandleList;
}

void ApexPriceHistory::FetchData()
{
	if (mPollable.TryHold() == false)
		return;

	mThreadPool.push_task([this] {
		Pollable::PollerRef ref = mPollable.CreateRef();

		httplib::Result res = mRequestBuilder
			.Reset()
			.setType("GET")
			.setEndpoint("/klines")
			.AddURLParam("symbol", mCurrencyPair.getPair())
			.AddURLParam("interval", std::to_string(mCandleInterval))
			.AddURLParam("limit", std::to_string(50))
			.Build()
			.Perform();

		if (!res)
			return;

		nlohmann::json kLinesJson;

		try {
			kLinesJson = nlohmann::json::parse(res->body);
			kLinesJson = kLinesJson["data"][mCurrencyPair.getPair()];
			mQueue.Enqueue(kLinesJson);
		}
		catch (...) {}
		});
}
