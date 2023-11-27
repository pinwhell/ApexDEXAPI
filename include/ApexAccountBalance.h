#pragma once

#include <IDataProvider.h>
#include <IDataProcessor.h>
#include <ApexRequest.h>
#include <BS_thread_pool_light.hpp>
#include <Pollable.h>
#include <SafeQueue.h>
#include <nlohmann/json.hpp>

class ApexAccountBalance : public IDataProvider, public IDataProcessor {
public:
	ApexAccountBalance(const ApexPrivateAPIRequestBuilder& requestBuilder, BS::thread_pool_light& threadPool);

	void FetchData() override;
	void ProcessData() override;
	double getTotalEquity();
	double getAvailableBalance();

private:
	ApexPrivateAPIRequestBuilder mRequestBuilder;
	Pollable mPollable;
	SafeQueue<nlohmann::json> mQueue;
	BS::thread_pool_light& mThreadPool;

	double mTotalEquity;
	double mAvailableBalance;
};