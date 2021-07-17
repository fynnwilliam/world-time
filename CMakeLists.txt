cmake_minimum_required(VERSION 3.18.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(time_api)

message(STATUS "Fetching curl")
include(FetchContent)
FetchContent_Declare(curl GIT_REPOSITORY https://github.com/curl/curl.git)
FetchContent_MakeAvailable(curl)

message(STATUS "Fetching curlpp")
FetchContent_Declare(curlpp GIT_REPOSITORY https://github.com/jpbarrette/curlpp.git)
FetchContent_MakeAvailable(curlpp)

add_executable(time src/world_time.cpp)

target_include_directories(time PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(time PUBLIC CURL::libcurl -lcurlpp)

#target_compile_options(time PRIVATE -w)