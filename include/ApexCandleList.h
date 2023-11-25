#pragma once

#include <ApexCandle.h>
#include <Cache.h>
#include <mutex>

class ApexCandleList : private Cache<ApexCandle> {
public:
	ApexCandleList(size_t cacheLen);

	void Update(const nlohmann::json& candlesJson);
	void ForEachCandle(std::function<bool(const ApexCandle&)> callback) const;
	void AddOnTickCallback(std::function<void(const ApexCandleList&)> callback);
	void UpdateCheckTick();
	size_t getCandlesCount();

	const Candle& operator[](const size_t idx) const;

private:
	void Add(const nlohmann::json& candleData);
	void ReportCallbacksTick();

	std::vector<std::function<void(const ApexCandleList&)>> mOnTickCallbacks;
	bool mPendingReportTick;
};

std::ostream& operator<<(std::ostream& stream, const ApexCandleList& candMgr);