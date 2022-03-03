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

if(MSVC)
  file(GLOB_RECURSE SRC_FILES src \*.cpp)
else()
  file(GLOB_RECURSE SRC_FILES src/*.cpp)
endif()
add_executable(time ${SRC_FILES})

target_include_directories(time PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(time PUBLIC CURL::libcurl -lcurlpp)

if (MSVC)
  target_compile_options(time PRIVATE \W4)
else()
  target_compile_options(time PRIVATE -w)
endif()