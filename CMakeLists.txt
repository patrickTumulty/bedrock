cmake_minimum_required(VERSION 3.16)

project(commonpp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DLIB_VERSION="${PROJECT_VERSION}")

file(GLOB COMMON_PP_HEADERS src/headers/*.h)
file(GLOB COMMON_PP_SOURCES src/sources/*.cpp)

include_directories(src/headers)

add_library(${PROJECT_NAME} STATIC ${COMMON_PP_HEADERS} ${COMMON_PP_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${COMMON_PP_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC "src/headers")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB COMMON_PP_TESTS tests/*.cpp tests/*.h)

add_executable(${PROJECT_NAME}_test ${COMMON_PP_TESTS} ${COMMON_PP_HEADERS} ${COMMON_PP_SOURCES})

target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
