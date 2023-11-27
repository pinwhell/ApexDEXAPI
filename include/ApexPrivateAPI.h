#pragma once

#include <BS_thread_pool_light.hpp>
#include <ApexRequest.h>
#include <IDataProvider.h>
#include <IDataProcessor.h>
#include <ApexAccountBalance.h>

class ApexPrivateAPI : public IDataProvider, public IDataProcessor {
public:
	ApexPrivateAPI(
		const ApexAPICredentials& apiCredentials,
		BS::thread_pool_light& threadPool,
		const std::string& baseUrl = "https://pro.apex.exchange",
		const std::string& version = "v1"
	);

	void FetchData() override;
	void ProcessData() override;

	ApexAccountBalance& getAccountBalance();

private:
	ApexPrivateAPIRequestBuilder mRequestBuilder;
	BS::thread_pool_light& mThreadPool;
	ApexAccountBalance mAccountBalance;
	std::vector<IDataProvider*> mDataProviders;
	std::vector<IDataProcessor*> mDataProcessors;
};