#include <Request.h>

Request::Request(
	const std::string& method,
	const std::string& schemaDomainPort,
	const std::string& fullPath,
	const std::vector<std::pair<std::string, std::string>>& headers,
	const std::vector<std::pair<std::string, std::string>>& urlEncodedParams
)
	: mSchemaDomainPort(schemaDomainPort)
	, mPath(fullPath)
	, mbHTTPS(schemaDomainPort.find("https") != std::string::npos)
	, mMethod(method)
	, mHeaders(headers)
	, mURLEncodedParams(urlEncodedParams)
{}

httplib::Result Request::Perform()
{
	httplib::Client client(mSchemaDomainPort);

	httplib::Headers headers;

	for (const std::pair<std::string, std::string>& header : mHeaders)
		headers.insert(header);

	if (mMethod == "GET")
		return client.Get(mPath, headers);

	if (mMethod == "POST")
	{
		httplib::Params params;

		for (const std::pair<std::string, std::string>& param : mURLEncodedParams)
			params.insert(param);

		return client.Post(mPath, headers, params);
	}

	/*if (mMethod == "PUT")
		return client.Put(mPath, headers);*/

	return client.Get(mPath, headers);
}

RequestBuilder::RequestBuilder()
{
	Reset();
}

RequestBuilder& RequestBuilder::Reset()
{
	mMethod = "GET";
	mSchemaDomainPort.clear();
	mPath = "/";
	mURLParams.clear();
	mFullPath.clear();
	mOnPreInstantiationCallbacks.clear();
	mURLEncodedParams.clear();
	mFullURLEncodedParams.clear();
	mHeaders.clear();
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

RequestBuilder& RequestBuilder::AddURLEncodedParam(const std::string& key, const std::string& val)
{
	mURLEncodedParams.push_back(std::make_pair(key, val));
	return *this;
}

RequestBuilder& RequestBuilder::setMethod(const std::string& type)
{
	mMethod = type;
	return *this;
}

RequestBuilder& RequestBuilder::AddOnPreInstantiationCallback(std::function<void(RequestBuilder&)> callback)
{
	mOnPreInstantiationCallbacks.push_back(callback);
	return *this;
}

RequestBuilder& RequestBuilder::AddHeader(const std::string& key, const std::string& val)
{
	mHeaders.emplace_back(std::make_pair(key, val));
	return *this;
}

Request RequestBuilder::Build()
{
	if (mMethod == "POST" && mURLEncodedParams.empty() == false)
	{
		std::sort(mURLEncodedParams.begin(), mURLEncodedParams.end());

		for (int i = 0; i < mURLEncodedParams.size(); i++)
		{
			const auto& param = mURLEncodedParams[i];

			if (i != 0)
				mFullURLEncodedParams += "&";

			mFullURLEncodedParams += param.first + "=" + param.second;
		}
	}

	mFullPath = mPath;

	if (mURLParams.empty() == true)
	{
		for (const auto& callback : mOnPreInstantiationCallbacks)
			callback(*this);

		return Request(mMethod, mSchemaDomainPort, mFullPath, mHeaders, mURLEncodedParams);
	}

	char urlParamDelim = mFullPath.find('?') == std::string::npos ? '?' : '&';

	for (const auto& urlParamKV : mURLParams)
	{
		std::string urlParamKVStr = urlParamKV.first + '=' + urlParamKV.second;
		mFullPath += urlParamDelim + urlParamKVStr;
		urlParamDelim = '&';
	}

	for (const auto& callback : mOnPreInstantiationCallbacks)
		callback(*this);

	return Request(mMethod, mSchemaDomainPort, mFullPath, mHeaders, mURLEncodedParams);
}

const std::string& RequestBuilder::getSortedURLEncodedParams() const
{
	return mFullURLEncodedParams;
}

const std::string& RequestBuilder::getFullPath() const
{
	return mFullPath;
}

const std::string& RequestBuilder::getMethod() const
{
	return mMethod;
}