cmake_minimum_required(VERSION 3.18.4)

set(CMAKE_CXX_STANDARD 20)

project(time_api)

message(STATUS "Fetching curlpp")
include(FetchContent)
FetchContent_Declare(curlpp
                     GIT_REPOSITORY https://github.com/jpbarrette/curlpp.git)
FetchContent_MakeAvailable(curlpp)

message(STATUS "Looking for curl")
find_package(CURL 7.74.0)

add_subdirectory(src)
