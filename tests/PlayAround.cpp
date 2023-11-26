#include <stdlib.h>
#include <stdio.h>
#include <ApexRequest.h>

int main()
{
	ApexAPICredentials apiCreds = ApexAPICredentials::FromEnviroment();

	if (!apiCreds)
	{
		printf("Authentication Error: Missing environment variables for API authentication.\nPlease verify that the following environment variables are set correctly:\nAPEX_API_KEY, APEX_API_SECRET, APEX_API_PASSPHRASE.\n");
		return 1;
	}

	ApexPrivateAPIRequestBuilder requestBuilder(apiCreds);

	httplib::Result res = requestBuilder
		.setMethod("GET")
		.setEndpoint("/account-balance")
		.Build()
		.Perform();

	if (!res)
	{
		printf("Request Failed\n");
		return 1;
	}

	std::cout << res->body << std::endl;
}