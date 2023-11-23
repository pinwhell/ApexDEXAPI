#pragma once

#include <ApexRequest.h>
#include <CurrencyPair.h>
#include <SafeQueue.h>
#include <nlohmann/json.hpp>
#include <Pollable.h>

class ApexTicker {
public:
	ApexTicker(const ApexAPIRequestBuilder& requestBuilder, const CurrencyPair& currencyPair);

	void Refresh();
	double getOraclePrice();

private:
	void PollData();

	ApexAPIRequestBuilder mRequestBuilder;
	CurrencyPair mCurrencyPair;
	SafeQueue<nlohmann::json> mQueue;
	Pollable mPollable;
	double mOraclePrice;
};