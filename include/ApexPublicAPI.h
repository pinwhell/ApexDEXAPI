#pragma once

#include <string>
#include <unordered_map>
#include <ApexPriceHistory.h>
#include <ApexTicker.h>
#include <ApexRequest.h>
#include <BS_thread_pool_light.hpp>

class ApexPublicAPI {
public:
	ApexPublicAPI(const std::string& baseUrl, const std::string& version = "v1");

	void Refresh(bool wait = false);
	ApexTicker& getTicker(const CurrencyPair& currencyPair);
	ApexPriceHistory& getPriceHistory(const CurrencyPair& currencyPair, size_t candlesInterval = 5);

private:

	template <typename T, typename Container, typename ...Args>
	T& getOrCreateObject(const std::string& objectUid, Container& container, Args&&... args);

	BS::thread_pool_light mThreadPool;
	ApexAPIRequestBuilder mRequestBuilder;
	std::unordered_map<std::string, std::unique_ptr<ApexTicker>> mAllTickers;
	std::unordered_map<std::string, std::unique_ptr<ApexPriceHistory>> mAllPriceHistories;
};

template<typename T, typename Container, typename ...Args>
inline T& ApexPublicAPI::getOrCreateObject(const std::string& objectUid, Container& container, Args && ...args) {
	if (container.find(objectUid) != container.end())
		return *container[objectUid];

	container[objectUid] = std::make_unique<T>(args...);

	return *container[objectUid];
}
