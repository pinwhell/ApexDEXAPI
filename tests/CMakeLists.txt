add_executable(CandleListTest "CandleListTest/test.cpp")
add_executable(CandleTest "CandleTest/test.cpp")
add_executable(ServerTimeEstimationTest "ServerTimeEstimationTest/test.cpp")

target_link_libraries(CandleListTest ApexDEXAPI doctest_with_main)
target_link_libraries(CandleTest ApexDEXAPI doctest_with_main)
target_link_libraries(ServerTimeEstimationTest ApexDEXAPI doctest_with_main)

add_executable(PlayAround PlayAround.cpp)
target_link_libraries(PlayAround ApexDEXAPI)