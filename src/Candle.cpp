#include <Candle.h>
#include <Util.h>

Candle::Candle() 
{}

Candle::Candle(uint64_t time, double open, double high, double low, double close, double volume)
	: mTime(time)
	, mOpen(open)
	, mHigh(high)
	, mLow(low)
	, mClose(close)
	, mVolume(volume)
{}

bool Candle::operator==(const Candle& rhs)
{
	if (mTime != rhs.mTime)
		return false;

	// At this point, Candles Time Match
	// Lets see what changed

	if (fabs(mOpen - rhs.mOpen) > DBL_EPSILON)
		return false;

	if (fabs(mHigh - rhs.mHigh) > DBL_EPSILON)
		return false;

	if (fabs(mLow - rhs.mLow) > DBL_EPSILON)
		return false;

	if (fabs(mClose - rhs.mClose) > DBL_EPSILON)
		return false;

	// At this point OHLC dint 

	return true;
}

bool Candle::operator!=(const Candle& rhs)
{
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& stream, const Candle& candle)
{
	stream << "T: " << Time2Str(candle.mTime / 1000) << std::endl;
	stream << "O: " << candle.mOpen << std::endl;
	stream << "H: " << candle.mHigh << std::endl;
	stream << "L: " << candle.mLow << std::endl;
	stream << "C: " << candle.mClose << std::endl << std::endl;

	return stream;
}

