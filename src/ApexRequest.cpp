#include <ApexRequest.h>

ApexAPIRequestBuilder::ApexAPIRequestBuilder(const std::string& baseUrl, const std::string& version)
	: mBaseURL(baseUrl)
	, mVersion(version)
{
	Reset();
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::Reset()
{
	mRequestBuilder.Reset();
	mRequestBuilder.setSchemaDomainPort(mBaseURL);
	return *this;
}

Request ApexAPIRequestBuilder::Build()
{
	Request&& request = mRequestBuilder.Build();

	Reset();

	return request;
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::AddURLParam(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddURLParam(key, val);
	return *this;
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::setEndpoint(const std::string& _endpoint)
{
	if (_endpoint.empty())
		return *this;

	std::string endpoint = (_endpoint[0] == '/' ? "" : "/") + _endpoint;

	mRequestBuilder.setPath("/api/" + mVersion + endpoint);
	return *this;
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::setType(const std::string& type)
{
	mRequestBuilder.setType(type);
	return *this;
}