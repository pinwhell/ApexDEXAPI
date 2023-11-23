#include <doctest/doctest.h>
#include <string>
#include <Candle.h>

TEST_CASE("Test Candle Equality")
{
	Candle lhs(0, 1.f, 1.2f, 1.4f, 1.6f, 1.8f);
	Candle rhs(0, 1.f, 1.2f, 1.4f, 1.6f, 20.f);

	CHECK(lhs == rhs);
}

TEST_CASE("Test Candle Unequality")
{
	Candle lhs(0, 1.f, 1.2f, 1.4f, 1.6f, 1.8f);
	Candle rhs(0, 1.f, 1.2f, 1.4f, 1.61f, 1.8f);

	CHECK(lhs != rhs);
}