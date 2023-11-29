#include <doctest/doctest.h>
#include <ApexAPI.h>
#include <Util.h>

// Maximum Prediciton Error 750ms
#define MAX_DEVIATION_ERROR 750ull

TEST_CASE("Server Time Estimation Test")
{
	ApexAPI api;
	ApexPublicAPI& pubApi = api.getPublicAPI();

	CHECK(pubApi.getServerTime());

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	CHECK(std::abs(long long(pubApi.getServerTime() - pubApi.getServerTime(true))) < MAX_DEVIATION_ERROR);
}