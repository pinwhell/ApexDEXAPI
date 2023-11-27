#pragma once

#include <string>

struct ApexAPICredentials {
	ApexAPICredentials();
	ApexAPICredentials(const std::string& apiKey, const std::string& apiSecret, const std::string& apiPassphrase);

	operator bool() const;
	static ApexAPICredentials FromEnviroment();

	std::string mAPIKey;
	std::string mAPISecret;
	std::string mAPIPassphrase;
};