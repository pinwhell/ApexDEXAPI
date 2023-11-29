file(GLOB APEX_API_SRC *.cpp)

add_library(ApexDEXAPI STATIC ${APEX_API_SRC})

target_link_libraries(ApexDEXAPI PUBLIC nlohmann_json httplib BSThreadPool)


# Install library files (if any)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ApexDEXAPI.lib
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)