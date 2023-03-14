cmake_minimum_required(VERSION 3.16)

project(commonpp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DLIB_VERSION=${PROJECT_VERSION})

file(GLOB COMMON_PP_HEADERS headers/*.h)
file(GLOB COMMON_PP_SOURCES sources/*.cpp)

include_directories(headers)

add_library(${PROJECT_NAME} STATIC ${COMMON_PP_HEADERS} ${COMMON_PP_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${COMMON_PP_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")
