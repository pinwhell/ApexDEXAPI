#include <iostream>
#include <ApexPublicAPI.h>

int main()
{
	BS::thread_pool_light threadPool(std::thread::hardware_concurrency());
	ApexPublicAPI api(threadPool);
	ApexPriceHistory& btcUsdcHistory = api.getPriceHistory(CurrencyPair("BTC", "USDC"));
	ApexTicker& btcUsdcTicker = api.getTicker(CurrencyPair("BTC", "USDC"));
	Scheduler scheduler(std::chrono::milliseconds(500));

	btcUsdcHistory.AddOnTickCallback([&](const ApexCandleList& candles) {
		std::cout << candles[0] << std::endl;
		std::cout << btcUsdcTicker.getOraclePrice() << std::endl << std::endl;
		printf("Server Time: %lld\nUSDC Step Size %lf\n", api.getServerTime(true), api.getSymbols().getCurrency("USDC").mStepSize);
		});

	while (true)
	{
		if (!scheduler)
			continue;

		api.FetchData();

		threadPool.wait_for_tasks();

		api.ProcessData();
		api.UpdateCheckTick();

		scheduler.PostExecuted();
	}
}