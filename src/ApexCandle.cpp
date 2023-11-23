#include <ApexCandle.h>

ApexCandle::ApexCandle(const nlohmann::json& candleData)
{
	Update(candleData);
}

void ApexCandle::Update(const nlohmann::json& candleData)
{
	mTime = candleData["t"].get<uint64_t>();
	mOpen = std::stod(candleData["o"].get<std::string>());
	mHigh = std::stod(candleData["h"].get<std::string>());
	mLow = std::stod(candleData["l"].get<std::string>());
	mClose = std::stod(candleData["c"].get<std::string>());
	mVolume = std::stod(candleData["v"].get<std::string>());
}
