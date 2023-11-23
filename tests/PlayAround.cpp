#include <string>
#include <iostream>
#include <ApexPriceHistory.h>
#include <ApexTicker.h>

int main()
{
	ApexAPIRequestBuilder builder("https://pro.apex.exchange", "v2");
	ApexPriceHistory priceHistory(builder, CurrencyPair("BTC", "USDC"), 5);
	ApexTicker ticker(builder, CurrencyPair("BTC", "USDC"));

	priceHistory.AddOnTickCallback([&](const ApexCandleList& candles) {
		std::cout << candles[0] << std::endl;
		std::cout << ticker.getOraclePrice() << std::endl << std::endl;
		});

	while (true)
	{
		ticker.Refresh();
		priceHistory.Refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}