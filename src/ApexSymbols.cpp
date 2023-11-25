#include <ApexSymbols.h>

ApexSymbols::ApexSymbols(const ApexAPIRequestBuilder& requstBuilder, BS::thread_pool_light& threadPool)
	: mRequestBuilder(requstBuilder)
	, mThreadPool(threadPool)
	, mbWantRefresh(true)
{}

void ApexSymbols::FetchData()
{
	if (mPollable.TryHold() == false)
		return;

	mThreadPool.push_task([this] {
		Pollable::PollerRef ref = mPollable.CreateRef();

		httplib::Result res = mRequestBuilder
			.setType("GET")
			.setEndpoint("/symbols")
			.Build()
			.Perform();

		if (!res)
			return;

		try {
			nlohmann::json resJson = nlohmann::json::parse(res->body);

			resJson = resJson["data"];

			mPerpetualContractsQueue.Enqueue(resJson["perpetualContract"]);
			mCurrenciesQueue.Enqueue(resJson["currency"]);
			mbWantRefresh = false;
		}
		catch (...) {}

		});
}

void ApexSymbols::ProcessData()
{
	ProcessCurrenciesDatas();
	ProcessPerpetualContractDatas();
}

const ApexPerpeturalContact& ApexSymbols::getPerpetualContact(const CurrencyPair& currencyPair)
{
	std::string currencyPairStr = currencyPair.getPair("-");

	if (mPerpetualContracts.find(currencyPairStr) != mPerpetualContracts.end())
		return mPerpetualContracts[currencyPairStr];

	static ApexPerpeturalContact nullPerpContract;

	nullPerpContract.mStepSize = 0.0;
	nullPerpContract.mTickSize = 0.0;

	return nullPerpContract;

}

const ApexCurrency& ApexSymbols::getCurrency(const std::string& currency)
{
	if (mCurrencies.find(currency) != mCurrencies.end())
		return mCurrencies[currency];

	static ApexCurrency nullCurrency;

	nullCurrency.mStepSize = 0.0;

	return nullCurrency;
}

void ApexSymbols::setWantRefresh(bool b)
{
	mbWantRefresh = b;
}

inline void ApexSymbols::ProcessCurrenciesDatas()
{
	mCurrenciesQueue.ProcessAll([this](const nlohmann::json& currencyDatas) {
		ProcessCurrenciesDatas(currencyDatas);
		});
}

inline void ApexSymbols::ProcessCurrenciesDatas(const nlohmann::json& currencyDatas)
{
	for (const nlohmann::json& currencyData : currencyDatas)
	{
		if (mCurrencies.find(currencyData["id"]) != mCurrencies.end())
			continue;

		ApexCurrency& apexCurrency = mCurrencies[currencyData["id"]];

		apexCurrency.mStepSize = std::stod(currencyData["stepSize"].get<std::string>());
	}
}

inline void ApexSymbols::ProcessPerpetualContractDatas()
{
	mPerpetualContractsQueue.ProcessAll([this](const nlohmann::json& perpetualDatas) {
		ProcessPerpetualContractDatas(perpetualDatas);
		});
}

inline void ApexSymbols::ProcessPerpetualContractDatas(const nlohmann::json& perpetualContractDatas)
{
	for (const nlohmann::json& perpetualContractData : perpetualContractDatas)
	{
		if (mPerpetualContracts.find(perpetualContractData["symbol"]) != mPerpetualContracts.end())
			continue;

		ApexPerpeturalContact& perpContract = mPerpetualContracts[perpetualContractData["symbol"]];

		perpContract.mStepSize = std::stod(perpetualContractData["stepSize"].get<std::string>());
		perpContract.mTickSize = std::stod(perpetualContractData["tickSize"].get<std::string>());
	}
}
