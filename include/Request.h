#pragma once

#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

class Request {
public:
	Request(const std::string& type, const std::string& schemaDomainPort, const std::string& fullPath);

	httplib::Result Perform();

private:
	std::string mSchemaDomainPort;
	std::string mPath;
	std::string mType;
	bool mbHTTPS;
};

struct RequestBuilder {
	RequestBuilder();

	RequestBuilder& Reset();
	RequestBuilder& setSchemaDomainPort(const std::string& schemaDomainPort);
	RequestBuilder& setPath(const std::string& path);
	RequestBuilder& AddURLParam(const std::string& key, const std::string& val);
	RequestBuilder& setType(const std::string& type);
	Request Build();

private:
	std::string mType;
	std::string mSchemaDomainPort;
	std::string mPath;
	std::vector<std::pair<std::string, std::string>> mURLParams;
};
