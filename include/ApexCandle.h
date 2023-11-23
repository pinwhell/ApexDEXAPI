#pragma once

#include <nlohmann/json.hpp>
#include <Candle.h>

struct ApexCandle : Candle {
	ApexCandle(const nlohmann::json& candleData);
	void Update(const nlohmann::json& candleData);
};
