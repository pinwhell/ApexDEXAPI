#pragma once

#include <cstdint>
#include <fstream>

struct Candle {

	Candle();
	Candle(uint64_t time, double open, double high, double low, double close, double volume);

	bool operator==(const Candle& rhs);
	bool operator!=(const Candle& rhs);

	uint64_t mTime;
	double mOpen;
	double mHigh;
	double mLow;
	double mClose;
	double mVolume;
};

std::ostream& operator<<(std::ostream& stream, const Candle& candle);
