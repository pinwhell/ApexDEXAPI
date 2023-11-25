#include <ApexCandleList.h>

ApexCandleList::ApexCandleList(size_t cacheLen)
	: mPendingReportTick(false)
{
	setMaxElements(cacheLen);
}

void ApexCandleList::Add(const nlohmann::json& candleData)
{
	ApexCandle candle(candleData);

	Push(candle);
}

void ApexCandleList::ReportCallbacksTick()
{
	for (const auto& onTickCallback : mOnTickCallbacks)
		onTickCallback(*this);
}

void ApexCandleList::Update(const nlohmann::json& candlesJson)
{
	if (candlesJson.empty())
		return;

	if (mCache.empty())
	{
		for (int i = 0; i < candlesJson.size(); i++)
			Add(candlesJson[i]);

		mPendingReportTick = true;

		return;
	}

	// Cache alredy initialized, 
	// lets simply update it

	ApexCandle cacheUpMostToDate = mCache.front();

	auto cachedHead = std::find_if(candlesJson.begin(), candlesJson.end(), [&](const nlohmann::json& candle) {
		return candle["t"].get<uint64_t>() == cacheUpMostToDate.mTime;
		});

	if (cachedHead == candlesJson.end())
		return;

	// Found Cache Head, lets start updating the head itself

	mCache.front().Update(*cachedHead); cachedHead++;

	for (; cachedHead < candlesJson.end(); cachedHead++)
		Add(*cachedHead);

	if (mCache.front() != cacheUpMostToDate)
		mPendingReportTick = true;
}

void ApexCandleList::UpdateCheckTick()
{
	if (!mPendingReportTick)
		return;

	ReportCallbacksTick();		

	mPendingReportTick = false;
}

const Candle& ApexCandleList::operator[](const size_t idx) const
{
	static Candle nullCandle(0, 0, 0, 0, 0, 0);

	if ((idx < mCache.size()) == false)
		return nullCandle;

	return mCache[idx];
}

void ApexCandleList::ForEachCandle(std::function<bool(const ApexCandle&)> callback) const {
	for (const ApexCandle& candle : mCache)
	{
		if (callback(candle) == false)
			return;
	}
}

void ApexCandleList::AddOnTickCallback(std::function<void(const ApexCandleList&)> callback)
{
	mOnTickCallbacks.push_back(callback);
}

size_t ApexCandleList::getCandlesCount()
{
	return mCache.size();
}

std::ostream& operator<<(std::ostream& stream, const ApexCandleList& candMgr)
{
	candMgr.ForEachCandle([&](const ApexCandle& cand) {
		stream << cand << std::endl;

		return true;
		});

	stream << "=====================================";

	return stream;
}