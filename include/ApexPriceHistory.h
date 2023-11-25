#pragma once

#include <ApexRequest.h>
#include <CurrencyPair.h>
#include <ApexCandleList.h>
#include <SafeQueue.h>
#include <Pollable.h>
#include <BS_thread_pool_light.hpp>
#include <IDataProvider.h>
#include <IDataProcessor.h>

class ApexPriceHistory : public IDataProvider, public IDataProcessor {
public:
	ApexPriceHistory(const ApexPriceHistory&) = delete;
	ApexPriceHistory(const ApexPriceHistory&&) = delete;
	ApexPriceHistory(const ApexAPIRequestBuilder& requestBuilder, const CurrencyPair& currencyPair, size_t candleInterval, BS::thread_pool_light& threadPool);
	void FetchData() override;
	void ProcessData() override;
	void AddOnTickCallback(std::function<void(const ApexCandleList&)> callback);
	void UpdateCheckTick();
	ApexCandleList& getCandles();

private:

	size_t			mCandleInterval;
	CurrencyPair	mCurrencyPair;
	ApexCandleList	mCandleList;
	Pollable		mPollable;
	ApexAPIRequestBuilder		mRequestBuilder;
	SafeQueue<nlohmann::json>	mQueue;
	BS::thread_pool_light& mThreadPool;
};