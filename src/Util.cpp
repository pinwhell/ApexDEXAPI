#include <Util.h>
#include <ctime>
#include <chrono>

std::string Time2Str(time_t time)
{
	struct tm* timeInfo = std::gmtime(&time);
	char formattedDate[80];
	std::strftime(formattedDate, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
	return std::string(formattedDate);
}

unsigned long long GetCurrentEpochMillis()
{
	using namespace std::chrono;
	auto now = system_clock::now();
	auto timeSinceEpoch = now.time_since_epoch();
	return duration_cast<milliseconds>(timeSinceEpoch).count();
}