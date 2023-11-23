#pragma once

#include <string>
#include <Request.h>

class ApexAPIRequestBuilder {
public:
	ApexAPIRequestBuilder(const std::string& baseUrl, const std::string& version = "v1");

	ApexAPIRequestBuilder& Reset();
	Request Build();
	ApexAPIRequestBuilder& AddURLParam(const std::string& key, const std::string& val);
	ApexAPIRequestBuilder& setEndpoint(const std::string& _endpoint);
	ApexAPIRequestBuilder& setType(const std::string& type);

private:
	RequestBuilder mRequestBuilder;
	std::string mBaseURL;
	std::string mVersion;
};