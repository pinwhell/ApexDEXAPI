#pragma once

#include <ApexRequest.h>
#include <IDataProvider.h>
#include <IDataProcessor.h>
#include <BS_thread_pool_light.hpp>
#include <Pollable.h>
#include <SafeQueue.h>
#include <nlohmann/json.hpp>
#include <CurrencyPair.h>

struct ApexCurrency {
	double mStepSize;
};

struct ApexPerpeturalContact {
	double mStepSize;
	double mTickSize;
};

class ApexSymbols : public IDataProvider, public IDataProcessor {

public:
	ApexSymbols(const ApexAPIRequestBuilder& requstBuilder, BS::thread_pool_light& threadPool);

	void FetchData() override;
	void ProcessData() override;
	const ApexPerpeturalContact& getPerpetualContact(const CurrencyPair& currencyPair);
	const ApexCurrency& getCurrency(const std::string& currency);
	void setWantRefresh(bool b);

private:
	void ProcessCurrenciesDatas();
	void ProcessCurrenciesDatas(const nlohmann::json& currencyDatas);
	void ProcessPerpetualContractDatas();
	void ProcessPerpetualContractDatas(const nlohmann::json& perpetualContractDatas);

	BS::thread_pool_light& mThreadPool;
	ApexAPIRequestBuilder mRequestBuilder;
	Pollable mPollable;
	SafeQueue<nlohmann::json> mCurrenciesQueue;
	SafeQueue<nlohmann::json> mPerpetualContractsQueue;
	std::unordered_map<std::string, ApexCurrency> mCurrencies;
	std::unordered_map<std::string, ApexPerpeturalContact> mPerpetualContracts;
	bool mbWantRefresh; // PlaceHolder => We need Refresh Interval Component
};