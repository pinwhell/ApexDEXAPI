#include <doctest/doctest.h>
#include <string>
#include <ApexCandleList.h>

TEST_CASE("Initial Update")
{
    std::string sample1 = R"({
    "data": {
        "BTCUSDC": [
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700438400000,
                "c": "37151",
                "h": "37416",
                "l": "37056",
                "o": "37395.5",
                "v": "347.786",
                "tr": "12951796.106"
            },
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700460000000,
                "c": "37183.5",
                "h": "37448.5",
                "l": "37076",
                "o": "37151",
                "v": "366.467",
                "tr": "13641790.1705"
            }
        ]
    },
    "timeCost": 3099613
})";

    ApexCandleList candleList(50);

    nlohmann::json sample1Json = nlohmann::json::parse(sample1);

    candleList.Update(sample1Json["data"]["BTCUSDC"]);

    CHECK(candleList[0].mTime == 1700460000000);
}

TEST_CASE("Refresh Test")
{
    std::string sample1 = R"({
    "data": {
        "BTCUSDC": [
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700438400000,
                "c": "37151",
                "h": "37416",
                "l": "37056",
                "o": "37395.5",
                "v": "347.786",
                "tr": "12951796.106"
            },
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700460000000,
                "c": "37183.5",
                "h": "37448.5",
                "l": "37076",
                "o": "37151",
                "v": "366.467",
                "tr": "13641790.1705"
            }
        ]
    },
    "timeCost": 3099613
})";

    std::string sample2 = R"({
    "data": {
        "BTCUSDC": [
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700438400000,
                "c": "37151",
                "h": "37416",
                "l": "37056",
                "o": "37395.5",
                "v": "347.786",
                "tr": "12951796.106"
            },
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700460000000,
                "c": "37184",
                "h": "37448.5",
                "l": "37076",
                "o": "37151",
                "v": "366.467",
                "tr": "13641790.1705"
            },
            {
                "s": "BTCUSDC",
                "i": "360",
                "t": 1700481600000,
                "c": "37613.5",
                "h": "37788.5",
                "l": "36688",
                "o": "37183.5",
                "v": "747.934",
                "tr": "27863935.9795"
            }
        ]
    },
    "timeCost": 3099613
})";

    ApexCandleList candleList(50);

    nlohmann::json sample1Json = nlohmann::json::parse(sample1);
    nlohmann::json sample2Json = nlohmann::json::parse(sample2);

    candleList.Update(sample1Json["data"]["BTCUSDC"]);

    CHECK_EQ(candleList[0].mClose, 37183.5);

    candleList.Update(sample2Json["data"]["BTCUSDC"]);

    CHECK_EQ(candleList[1].mClose, 37184);
    CHECK   (candleList[0].mTime == 1700481600000);
}