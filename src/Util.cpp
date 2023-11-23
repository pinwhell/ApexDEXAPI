#include <Util.h>
#include <ctime>

std::string Time2Str(time_t time)
{
	struct tm* timeInfo = std::gmtime(&time);
	char formattedDate[80];
	std::strftime(formattedDate, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
	return std::string(formattedDate);
}