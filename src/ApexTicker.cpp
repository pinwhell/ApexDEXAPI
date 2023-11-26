#include <ApexTicker.h>

ApexTicker::ApexTicker(const ApexAPIRequestBuilder& requestBuilder, const CurrencyPair& currencyPair, BS::thread_pool_light& threadPool)
	: mRequestBuilder(requestBuilder)
	, mCurrencyPair(currencyPair)
	, mOraclePrice(0.f)
	, mThreadPool(threadPool)
{}

void ApexTicker::ProcessData()
{
	mQueue.ProcessAll([&](const nlohmann::json& data) {
		mOraclePrice = std::stod(data["oraclePrice"].get<std::string>());
		});
}

double ApexTicker::getOraclePrice() const
{
	return mOraclePrice;
}

void ApexTicker::FetchData()
{
	if (mPollable.TryHold() == false)
		return;

	mThreadPool.push_task([this] {

		Pollable::PollerRef ref = mPollable.CreateRef();

		httplib::Result res = mRequestBuilder
			.Reset()
			.setMethod("GET")
			.setEndpoint("/ticker")
			.AddURLParam("symbol", mCurrencyPair.getPair())
			.Build()
			.Perform();

		if (!res)
			return;

		try {
			nlohmann::json tickerData = nlohmann::json::parse(res->body);
			tickerData = tickerData["data"][0];
			mQueue.Enqueue(tickerData);
		}
		catch (...) {}

		});
}