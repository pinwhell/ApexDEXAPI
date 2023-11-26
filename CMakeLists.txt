cmake_minimum_required(VERSION 3.20)

project(ApexDEXAPI)

set(CMAKE_CXX_STANDARD 17)

include_directories(include include/Interfaces)

add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)