add_subdirectory(doctest)
add_subdirectory(json)
add_subdirectory(openssl-3.0)

add_library(httplib INTERFACE)
target_include_directories(httplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cpp-httplib)
target_link_libraries(httplib INTERFACE openssl)