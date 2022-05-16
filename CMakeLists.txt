cmake_minimum_required(VERSION 3.16)
project(CommonPP)

set(CMAKE_CXX_STANDARD 17)

file(GLOB COMMON_PP_HEADERS headers/*.h)
file(GLOB COMMON_PP_SOURCES sources/*.cpp)

include_directories(headers)

add_library(CommonPP ${COMMON_PP_HEADERS} ${COMMON_PP_SOURCES})