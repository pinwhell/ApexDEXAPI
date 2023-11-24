#pragma once

#include <string>

struct CurrencyPair {
	CurrencyPair(const std::string& currencyA, const std::string& currencyB);

	std::string getPair() const;

	std::string mCurrencyA;
	std::string mCurrencyB;
};