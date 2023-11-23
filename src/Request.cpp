#include <Request.h>

Request::Request(const std::string& type, const std::string& schemaDomainPort, const std::string& fullPath)
	: mSchemaDomainPort(schemaDomainPort)
	, mPath(fullPath)
	, mbHTTPS(schemaDomainPort.find("https") != std::string::npos)
	, mType(type)
{}

httplib::Result Request::Perform()
{
	httplib::Client client(mSchemaDomainPort);

	if (mType == "GET")
		return client.Get(mPath);

	if (mType == "POST")
		return client.Post(mPath);

	if (mType == "PUT")
		return client.Put(mPath);

	return client.Get(mPath);
}

RequestBuilder::RequestBuilder()
{
	Reset();
}

RequestBuilder& RequestBuilder::Reset()
{
	mType = "GET";
	mSchemaDomainPort.clear();
	mPath.clear();
	mURLParams.clear();
	return *this;
}

RequestBuilder& RequestBuilder::setSchemaDomainPort(const std::string& schemaDomainPort)
{
	mSchemaDomainPort = schemaDomainPort;
	return *this;
}

RequestBuilder& RequestBuilder::setPath(const std::string& path)
{
	mPath = path;
	return *this;
}

RequestBuilder& RequestBuilder::AddURLParam(const std::string& key, const std::string& val)
{
	mURLParams.push_back(std::make_pair(key, val));
	return *this;
}

RequestBuilder& RequestBuilder::setType(const std::string& type)
{
	mType = type;
	return *this;
}

Request RequestBuilder::Build()
{
	if (mURLParams.empty() == true)
		return Request(mType, mSchemaDomainPort, mPath);

	std::string fullPath = mPath;

	char urlParamDelim = fullPath.find('?') == std::string::npos ? '?' : '&';

	for (const auto& urlParamKV : mURLParams)
	{
		std::string urlParamKVStr = urlParamKV.first + '=' + urlParamKV.second;
		fullPath += urlParamDelim + urlParamKVStr;
		urlParamDelim = '&';
	}

	return Request(mType, mSchemaDomainPort, fullPath);
}