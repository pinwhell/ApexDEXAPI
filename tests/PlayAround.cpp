#include <iostream>
#include <ApexPublicAPI.h>
#include <Cache.h>
#include <IDataProvider.h>
#include <IDataProcessor.h>

int main()
{
	ApexPublicAPI api("https://pro.apex.exchange", "v1");
	ApexPriceHistory& btcUsdcHistory = api.getPriceHistory(CurrencyPair("BTC", "USDC"));
	ApexTicker& btcUsdcTicker = api.getTicker(CurrencyPair("BTC", "USDC"));

	btcUsdcHistory.AddOnTickCallback([&](const ApexCandleList& candles) {
		std::cout << candles[0] << std::endl;
		std::cout << btcUsdcTicker.getOraclePrice() << std::endl << std::endl;
		printf("Server Time: %lld\nUSDC Step Size %lf\n", api.getServerTime(true), api.getSymbols().getCurrency("USDC").mStepSize);
		});

	while (true)
	{
		api.Refresh();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}