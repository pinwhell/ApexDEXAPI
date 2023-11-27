#include <iostream>
#include <ApexPrivateAPI.h>
#include <Scheduler.h>

int main()
{
	ApexAPICredentials apiCreds = ApexAPICredentials::FromEnviroment();

	if (!apiCreds)
	{
		printf("Authentication Error: Missing environment variables for API authentication.\nPlease verify that the following environment variables are set correctly:\nAPEX_API_KEY, APEX_API_SECRET, APEX_API_PASSPHRASE.\n");
		return 1;
	}

	BS::thread_pool_light threadPool(std::thread::hardware_concurrency());
	ApexPrivateAPI api(apiCreds, threadPool);
	Scheduler scheduler(std::chrono::milliseconds(500));

	while (true)
	{
		if (!scheduler)
			continue;

		api.FetchData();

		threadPool.wait_for_tasks();

		api.ProcessData();

		system("cls");

		std::cout << "Full Account Equity: " << api.getAccountBalance().getTotalEquity() << std::endl;

		scheduler.PostExecuted();
	}
}