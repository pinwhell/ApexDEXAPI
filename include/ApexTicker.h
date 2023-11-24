#pragma once

#include <ApexRequest.h>
#include <CurrencyPair.h>
#include <SafeQueue.h>
#include <nlohmann/json.hpp>
#include <Pollable.h>
#include <BS_thread_pool_light.hpp>

class ApexTicker {
public:
	ApexTicker(const ApexTicker&) = delete;
	ApexTicker(const ApexTicker&&) = delete;
	ApexTicker(const ApexAPIRequestBuilder& requestBuilder, const CurrencyPair& currencyPair, BS::thread_pool_light& threadPool);

	void Refresh();
	double getOraclePrice();

private:
	void PollData();

	ApexAPIRequestBuilder mRequestBuilder;
	CurrencyPair mCurrencyPair;
	SafeQueue<nlohmann::json> mQueue;
	Pollable mPollable;
	BS::thread_pool_light& mThreadPool;
	double mOraclePrice;
};