#pragma once

#include <string>
#include <Request.h>
#include <ApexAPICredentials.h>

class ApexAPIRequestBuilder {
public:
	ApexAPIRequestBuilder(const std::string& baseUrl = "https://pro.apex.exchange", const std::string& version = "v1");

	ApexAPIRequestBuilder& Reset();
	Request Build();
	ApexAPIRequestBuilder& AddURLParam(const std::string& key, const std::string& val);
	ApexAPIRequestBuilder& AddURLEncodedParam(const std::string& key, const std::string& val);
	ApexAPIRequestBuilder& AddHeader(const std::string& key, const std::string& val);
	ApexAPIRequestBuilder& setEndpoint(const std::string& _endpoint);
	ApexAPIRequestBuilder& setMethod(const std::string& method);
	ApexAPIRequestBuilder& AddOnPreInstantiationCallback(std::function<void(RequestBuilder&)> callback);

private:
	RequestBuilder mRequestBuilder;
	std::string mBaseURL;
	std::string mVersion;
};

class ApexPrivateAPIRequestBuilder {
public:
	ApexPrivateAPIRequestBuilder(ApexAPICredentials credentials, const std::string& baseUrl = "https://pro.apex.exchange", const std::string& version = "v1");
	ApexPrivateAPIRequestBuilder& Reset();
	Request Build();
	ApexPrivateAPIRequestBuilder& AddURLParam(const std::string& key, const std::string& val);
	ApexPrivateAPIRequestBuilder& AddURLEncodedParam(const std::string& key, const std::string& val);
	ApexPrivateAPIRequestBuilder& AddHeader(const std::string& key, const std::string& val);
	ApexPrivateAPIRequestBuilder& setEndpoint(const std::string& _endpoint);
	ApexPrivateAPIRequestBuilder& setMethod(const std::string& method);

private:
	ApexAPIRequestBuilder mRequestBuilder;
	ApexAPICredentials mCredentials;
};