#include <stdio.h>
#include <ApexAPI.h>

int main()
{
	ApexAPICredentials apiCreds = ApexAPICredentials::FromEnviroment();

	if (!apiCreds)
	{
		printf("Authentication Error: Missing environment variables for API authentication.\nPlease verify that the following environment variables are set correctly:\nAPEX_API_KEY, APEX_API_SECRET, APEX_API_PASSPHRASE.\n");
		return 1;
	}

	ApexAPI apexApi(apiCreds);

	apexApi.Refresh(true);

	std::cout << "Full Account Equity: " << apexApi.getPrivateAPI().getAccountBalance().getTotalEquity() << std::endl;
}