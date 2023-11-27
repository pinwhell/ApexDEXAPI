#pragma once

#include <string>
#include <unordered_map>
#include <ApexPriceHistory.h>
#include <ApexTicker.h>
#include <ApexRequest.h>
#include <ApexSymbols.h>
#include <BS_thread_pool_light.hpp>

class ApexPublicAPI : public IDataProvider, public IDataProcessor {
public:
	ApexPublicAPI(
		BS::thread_pool_light& threadPool,
		const std::string& baseUrl = "https://pro.apex.exchange",
		const std::string& version = "v1"
	);

	void FetchData() override;
	void ProcessData() override;

	void UpdateCheckTick();
	ApexTicker& getTicker(const CurrencyPair& currencyPair);
	ApexPriceHistory& getPriceHistory(const CurrencyPair& currencyPair, size_t candlesInterval = 5);
	ApexSymbols& getSymbols();
	unsigned long long getServerTime(bool estimate = false);

private:

	template <typename T, typename Container, typename ...Args>
	inline T& getOrCreateObject(const std::string& objectUid, Container& container, Args && ...args) {
		if (container.find(objectUid) != container.end())
			return *container[objectUid];

		container[objectUid] = std::make_unique<T>(args...);

		mDataProviders.push_back(container[objectUid].get());
		mDataProcessors.push_back(container[objectUid].get());

		return *container[objectUid];
	}

	ApexAPIRequestBuilder mRequestBuilder;
	BS::thread_pool_light& mThreadPool;
	ApexSymbols mSymbols;
	std::vector<IDataProvider*> mDataProviders;
	std::vector<IDataProcessor*> mDataProcessors;
	std::unordered_map<std::string, std::unique_ptr<ApexTicker>> mAllTickers;
	std::unordered_map<std::string, std::unique_ptr<ApexPriceHistory>> mAllPriceHistories;
};


