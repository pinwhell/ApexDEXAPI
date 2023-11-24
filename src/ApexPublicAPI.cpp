#include <ApexPublicAPI.h>

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

void ApexPublicAPI::Refresh(bool wait)
{
	for (const auto& ticker : mAllTickers)
		ticker.second->Refresh();

	for (const auto& history : mAllPriceHistories)
		history.second->Refresh();

	if (wait)
		mThreadPool.wait_for_tasks();
}
