cmake_minimum_required(VERSION 3.20)

project(ApexDEXAPI)

include_directories(include)

add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(tests)