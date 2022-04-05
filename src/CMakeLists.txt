add_library(timezn timezn.cpp)
if(MSVC)
  target_include_directories(timezn PUBLIC ..\include)
else()
  target_include_directories(timezn PUBLIC ../include)
endif()

add_library(timezns timezns.cpp)
target_link_libraries(timezns PUBLIC timezn)

add_library(app app.cpp)
target_link_libraries(app PUBLIC CURL::libcurl -lcurlpp timezns)

add_executable(time main.cpp)
target_link_libraries(time PUBLIC app)

if(MSVC)
  target_compile_options(time PRIVATE \W4)
else()
  target_compile_options(time PRIVATE -Wall -Wextra -O3)
endif()
