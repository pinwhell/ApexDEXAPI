#include <ApexRequest.h>
#include <Util.h>

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
	return mRequestBuilder.Build();
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::AddURLParam(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddURLParam(key, val);
	return *this;
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::AddURLEncodedParam(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddURLEncodedParam(key, val);
	return *this;
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::AddHeader(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddHeader(key, val);
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

ApexAPIRequestBuilder& ApexAPIRequestBuilder::setMethod(const std::string& method)
{
	mRequestBuilder.setMethod(method);
	return *this;
}

ApexAPIRequestBuilder& ApexAPIRequestBuilder::AddOnPreInstantiationCallback(std::function<void(RequestBuilder&)> callback)
{
	mRequestBuilder.AddOnPreInstantiationCallback(callback);
	return *this;
}

ApexPrivateAPIRequestBuilder::ApexPrivateAPIRequestBuilder(ApexAPICredentials credentials, const std::string& baseUrl, const std::string& version)
	: mRequestBuilder(baseUrl, version)
	, mCredentials(credentials)
{
	Reset();
}

ApexPrivateAPIRequestBuilder& ApexPrivateAPIRequestBuilder::Reset()
{
	mRequestBuilder.Reset();
	mRequestBuilder.AddOnPreInstantiationCallback([this](RequestBuilder& builder) {

		std::string nowTimeStampMillisStr = std::to_string(GetCurrentEpochMillis());

		std::string fullMsg = 
			nowTimeStampMillisStr +
			builder.getMethod() +
			builder.getFullPath() +
			(builder.getMethod() == "POST" ?
				builder.getSortedURLEncodedParams() :
				"");

		builder
			.AddHeader("APEX-TIMESTAMP", nowTimeStampMillisStr)
			.AddHeader("APEX-API-KEY", mCredentials.mAPIKey)
			.AddHeader("APEX-PASSPHRASE", mCredentials.mAPIPassphrase)
			.AddHeader("APEX-SIGNATURE", HMACSHA256(fullMsg, B64Encode(mCredentials.mAPISecret)));
		});

	return *this;
}

Request  ApexPrivateAPIRequestBuilder::Build()
{
	return mRequestBuilder.Build();
}

ApexPrivateAPIRequestBuilder& ApexPrivateAPIRequestBuilder::AddURLParam(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddURLParam(key, val);
	return *this;
}

ApexPrivateAPIRequestBuilder& ApexPrivateAPIRequestBuilder::AddURLEncodedParam(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddURLEncodedParam(key, val);
	return *this;
}

ApexPrivateAPIRequestBuilder& ApexPrivateAPIRequestBuilder::AddHeader(const std::string& key, const std::string& val)
{
	mRequestBuilder.AddHeader(key, val);
	return *this;
}

ApexPrivateAPIRequestBuilder& ApexPrivateAPIRequestBuilder::setEndpoint(const std::string& _endpoint)
{
	mRequestBuilder.setEndpoint(_endpoint);
	return *this;
}

ApexPrivateAPIRequestBuilder& ApexPrivateAPIRequestBuilder::setMethod(const std::string& method)
{
	mRequestBuilder.setMethod(method);
	return *this;
}