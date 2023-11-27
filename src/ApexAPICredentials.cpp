#include <ApexAPICredentials.h>
#include <stdlib.h>

ApexAPICredentials::ApexAPICredentials()
	: ApexAPICredentials("", "", "")
{}

ApexAPICredentials::ApexAPICredentials(const std::string& apiKey, const std::string& apiSecret, const std::string& apiPassphrase)
	: mAPIKey(apiKey)
	, mAPISecret(apiSecret)
	, mAPIPassphrase(apiPassphrase)
{}

ApexAPICredentials::operator bool() const
{
	return mAPIKey.empty() == false &&
		mAPISecret.empty() == false &&
		mAPIPassphrase.empty() == false;
}

ApexAPICredentials ApexAPICredentials::FromEnviroment()
{
	const char* apiKey = getenv("APEX_API_KEY");
	const char* apiSecret = getenv("APEX_API_SECRET");
	const char* apiPassphrase = getenv("APEX_API_PASSPHRASE");

	return ApexAPICredentials(apiKey ? apiKey : "", apiSecret ? apiSecret : "", apiPassphrase ? apiPassphrase : "");
}
