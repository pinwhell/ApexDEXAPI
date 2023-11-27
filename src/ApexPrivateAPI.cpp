#include <ApexPrivateAPI.h>

ApexPrivateAPI::ApexPrivateAPI(
	const ApexAPICredentials& apiCredentials,
	BS::thread_pool_light& threadPool,
	const std::string& baseUrl,
	const std::string& version
)	
	: mRequestBuilder(apiCredentials)
	, mThreadPool(threadPool)
	, mAccountBalance(mRequestBuilder, mThreadPool)
{
	if (!apiCredentials)
		return;

	mDataProviders.push_back(&mAccountBalance);
	mDataProcessors.push_back(&mAccountBalance);
}

void ApexPrivateAPI::FetchData()
{
	for (IDataProvider* provider : mDataProviders)
		provider->FetchData();
}

void ApexPrivateAPI::ProcessData()
{
	for (IDataProcessor* processor : mDataProcessors)
		processor->ProcessData();
}


ApexAccountBalance& ApexPrivateAPI::getAccountBalance()
{
	return mAccountBalance;
}
