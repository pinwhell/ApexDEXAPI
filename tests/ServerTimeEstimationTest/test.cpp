#include <doctest/doctest.h>
#include <ApexPublicAPI.h>
#include <Util.h>

// Maximum Prediciton Error 250ms
#define MAX_DEVIATION_ERROR 250ull

unsigned long long lastServerTimeEpoch = 0;
unsigned long long lastServerTimeReqLocalEpoch = 0;

unsigned long long EstimateServerEpoch()
{
	return lastServerTimeEpoch + (GetCurrentEpochMillis() - lastServerTimeReqLocalEpoch);
}

TEST_CASE("Server Time Estimation Test")
{
	ApexPublicAPI publicApi("https://pro.apex.exchange");

	lastServerTimeEpoch = publicApi.getServerTime();
	lastServerTimeReqLocalEpoch = GetCurrentEpochMillis();

	CHECK(lastServerTimeEpoch);

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	CHECK(std::abs(long long(publicApi.getServerTime() - EstimateServerEpoch())) < MAX_DEVIATION_ERROR);
}