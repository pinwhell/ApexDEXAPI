#include <ApexAPI.h>

ApexAPI::ApexAPI(const ApexAPICredentials& creds, const std::string& baseUrl, const std::string& version)
	: mThreadPool(std::thread::hardware_concurrency())
	, mPublicAPI(mThreadPool, baseUrl, version)
	, mPrivateAPI(creds, mThreadPool, baseUrl, version)
	, mRefreshCounts(0)
{}

void ApexAPI::Refresh(bool wait)
{
	wait = wait || mRefreshCounts++ == 0;

	mPrivateAPI.FetchData();
	mPublicAPI.FetchData();

	if (wait)
		mThreadPool.wait_for_tasks();

	mPrivateAPI.ProcessData();
	mPublicAPI.ProcessData();

	mPublicAPI.UpdateCheckTick();
}

ApexPublicAPI& ApexAPI::getPublicAPI()
{
	return mPublicAPI;
}

ApexPrivateAPI& ApexAPI::getPrivateAPI()
{
	return mPrivateAPI;
}
