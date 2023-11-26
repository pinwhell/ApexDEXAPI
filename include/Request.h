#pragma once

#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

class Request {
public:
	Request(
		const std::string& method,
		const std::string& schemaDomainPort,
		const std::string& fullPath,
		const std::vector<std::pair<std::string, std::string>>& headers,
		const std::vector<std::pair<std::string, std::string>>& urlEncodedParams);

	httplib::Result Perform();

private:
	std::string mSchemaDomainPort;
	std::string mPath;
	std::string mMethod;
	std::vector<std::pair<std::string, std::string>> mHeaders;
	std::vector<std::pair<std::string, std::string>> mURLEncodedParams;
	bool mbHTTPS;
};

struct RequestBuilder {
	RequestBuilder();

	RequestBuilder& Reset();
	RequestBuilder& setSchemaDomainPort(const std::string& schemaDomainPort);
	RequestBuilder& setPath(const std::string& path);
	RequestBuilder& setMethod(const std::string& type);
	RequestBuilder& AddURLParam(const std::string& key, const std::string& val);
	RequestBuilder& AddURLEncodedParam(const std::string& key, const std::string& val);
	RequestBuilder& AddHeader(const std::string& key, const std::string& val);
	RequestBuilder& AddOnPreInstantiationCallback(std::function<void(RequestBuilder&)> callback);
	Request Build();

	const std::string& getSortedURLEncodedParams() const;
	const std::string& getFullPath() const;
	const std::string& getMethod() const;

private:
	std::vector<std::function<void(RequestBuilder&)>> mOnPreInstantiationCallbacks;
	std::string mMethod;
	std::string mSchemaDomainPort;
	std::string mPath;
	std::string mFullPath;
	std::string mFullURLEncodedParams;
	std::vector<std::pair<std::string, std::string>> mURLParams;
	std::vector<std::pair<std::string, std::string>> mURLEncodedParams;
	std::vector<std::pair<std::string, std::string>> mHeaders;

};
