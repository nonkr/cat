cmake_minimum_required(VERSION 2.8)

project(c_datetime)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -DORGRIM_DEBUG")

add_executable(strftime strftime.c)
add_executable(strptime strptime.c)
add_executable(microsecond microsecond.cpp)
add_executable(chinese_calendar chinese_calendar.c)
add_executable(epoch epoch.c)
