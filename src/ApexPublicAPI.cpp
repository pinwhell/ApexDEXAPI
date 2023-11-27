#include <ApexPublicAPI.h>
#include <Util.h>

ApexPublicAPI::ApexPublicAPI(
	BS::thread_pool_light& threadPool,
	const std::string& baseUrl,
	const std::string& version
)
	: mRequestBuilder(baseUrl, version)
	, mThreadPool(threadPool)
	, mSymbols(mRequestBuilder, mThreadPool)
{
	mDataProviders.push_back(&mSymbols);
	mDataProcessors.push_back(&mSymbols);
}

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
		.setMethod("GET")
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

void ApexPublicAPI::FetchData()
{
	for (IDataProvider* provider : mDataProviders)
		provider->FetchData();
}

void ApexPublicAPI::ProcessData()
{
	for (IDataProcessor* processor : mDataProcessors)
		processor->ProcessData();
}

void ApexPublicAPI::UpdateCheckTick()
{
	for (const auto& history : mAllPriceHistories)
		history.second->UpdateCheckTick();
}

ApexSymbols& ApexPublicAPI::getSymbols()
{
	return mSymbols;
}
