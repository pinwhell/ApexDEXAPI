#include <ApexPublicAPI.h>
#include <Util.h>

ApexPublicAPI::ApexPublicAPI(const std::string& baseUrl, const std::string& version)
	: mRequestBuilder(baseUrl, version)
	, mThreadPool(std::thread::hardware_concurrency())
{}

ApexPriceHistory& ApexPublicAPI::getPriceHistory(const CurrencyPair & currencyPair, size_t candlesInterval)
{
	return getOrCreateObject<ApexPriceHistory>(currencyPair.getPair(), mAllPriceHistories,
		/*ApexPriceHistory Object Creation Params*/ mRequestBuilder, currencyPair, candlesInterval, mThreadPool);
}

ApexTicker& ApexPublicAPI::getTicker(const CurrencyPair& currencyPair)
{
	return getOrCreateObject<ApexTicker>(currencyPair.getPair(), mAllTickers,
		/*Ticker Object Creation Params*/ mRequestBuilder, currencyPair, mThreadPool);
}

unsigned long long ApexPublicAPI::getServerTime(bool estimate)
{
	static unsigned long long lastServerEpoch = 0;
	static unsigned long long lastServerTimeRequestLocalEpoch = 0;

	if (estimate && lastServerEpoch && lastServerTimeRequestLocalEpoch)
		return lastServerEpoch + (GetCurrentEpochMillis() - lastServerTimeRequestLocalEpoch);

	ApexAPIRequestBuilder reqBuilder = mRequestBuilder;

	httplib::Result res = reqBuilder
		.setType("GET")
		.setEndpoint("/time")
		.Build()
		.Perform();

	unsigned long long currentServerTimeRequestLocalEpoch = GetCurrentEpochMillis();

	if (!res)
		return 0;

	try {
		nlohmann::json svDate = nlohmann::json::parse(res->body);
		svDate = svDate["data"];
		lastServerTimeRequestLocalEpoch = currentServerTimeRequestLocalEpoch;
		return lastServerEpoch = svDate["time"];
	}
	catch (...) {}

	return 0;
}

void ApexPublicAPI::Refresh(bool wait)
{
	for (const auto& ticker : mAllTickers)
		ticker.second->Refresh();

	for (const auto& history : mAllPriceHistories)
		history.second->Refresh();

	if (wait)
		mThreadPool.wait_for_tasks();
}
