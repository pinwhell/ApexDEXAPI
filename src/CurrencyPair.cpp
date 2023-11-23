#include <CurrencyPair.h>

CurrencyPair::CurrencyPair(const std::string& currencyA, const std::string& currencyB)
	: mCurrencyA(currencyA)
	, mCurrencyB(currencyB)
{}

std::string CurrencyPair::getPair()
{
	return mCurrencyA + mCurrencyB;
}