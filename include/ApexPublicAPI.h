#pragma once

#include <string>
#include <unordered_map>
#include <ApexPriceHistory.h>
#include <ApexTicker.h>
#include <ApexRequest.h>
#include <ApexSymbols.h>
#include <BS_thread_pool_light.hpp>

class ApexPublicAPI {
public:
	ApexPublicAPI(const std::string& baseUrl, const std::string& version = "v1");

	void Refresh(bool wait = false);
	ApexTicker& getTicker(const CurrencyPair& currencyPair);
	ApexPriceHistory& getPriceHistory(const CurrencyPair& currencyPair, size_t candlesInterval = 5);
	ApexSymbols& getSymbols();
	unsigned long long getServerTime(bool estimate = false);

private:

	template <typename T, typename Container, typename ...Args>
	T& getOrCreateObject(const std::string& objectUid, Container& container, Args&&... args);

	template <typename T, typename Container>
	T& Push(Container& container, T& obj);

	ApexAPIRequestBuilder mRequestBuilder;
	BS::thread_pool_light mThreadPool;
	ApexSymbols mSymbols;
	std::vector<IDataProvider*> mDataProviders;
	std::vector<IDataProcessor*> mDataProcessors;
	std::unordered_map<std::string, std::unique_ptr<ApexTicker>> mAllTickers;
	std::unordered_map<std::string, std::unique_ptr<ApexPriceHistory>> mAllPriceHistories;
	size_t mRefreshCounts;
};

template<typename T, typename Container, typename ...Args>
inline T& ApexPublicAPI::getOrCreateObject(const std::string& objectUid, Container& container, Args && ...args) {
	if (container.find(objectUid) != container.end())
		return *container[objectUid];

	container[objectUid] = std::make_unique<T>(args...);

	Push(mDataProviders, *container[objectUid]);
	Push(mDataProcessors, *container[objectUid]);

	return *container[objectUid];
}

template <typename T, typename Container>
inline T& ApexPublicAPI::Push(Container& container, T& obj)
{
	container.push_back(&obj);

	return obj;
}
