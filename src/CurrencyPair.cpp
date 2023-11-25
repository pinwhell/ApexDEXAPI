#include <CurrencyPair.h>

CurrencyPair::CurrencyPair(const std::string& currencyA, const std::string& currencyB)
	: mCurrencyA(currencyA)
	, mCurrencyB(currencyB)
{}

std::string CurrencyPair::getPair(const std::string& separator) const
{
	if (separator.empty())
		return mCurrencyA + mCurrencyB;

	return  mCurrencyA + separator + mCurrencyB;;
}