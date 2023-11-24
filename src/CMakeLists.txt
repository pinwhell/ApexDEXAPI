file(GLOB APEX_API_SRC *.cpp)

add_library(ApexDEXAPI STATIC ${APEX_API_SRC})

target_link_libraries(ApexDEXAPI PUBLIC nlohmann_json httplib BSThreadPool)