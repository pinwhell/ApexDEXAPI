#pragma once

#include <ApexPublicAPI.h>
#include <ApexPrivateAPI.h>

class ApexAPI {
public:
	ApexAPI(const ApexAPICredentials& creds = ApexAPICredentials(), const std::string& baseUrl = "https://pro.apex.exchange", const std::string& version = "v1");

	void Refresh(bool wait = false);

	ApexPublicAPI& getPublicAPI();
	ApexPrivateAPI& getPrivateAPI();

private:
	BS::thread_pool_light mThreadPool;

	ApexPublicAPI mPublicAPI;
	ApexPrivateAPI mPrivateAPI;

	size_t mRefreshCounts;
};