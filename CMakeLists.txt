cmake_minimum_required(VERSION 3.16)

project(bedrock VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DLIB_VERSION="${PROJECT_VERSION}")

include(FetchContent)
FetchContent_Declare(
        tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG        v3.3.0
)
FetchContent_MakeAvailable(tomlplusplus)

file(GLOB BEDROCK_HEADERS src/headers/*.h)
file(GLOB BEDROCK_SOURCES src/sources/*.cpp)

include_directories(src/headers)

add_library(${PROJECT_NAME} STATIC ${BEDROCK_HEADERS} ${BEDROCK_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE tomlplusplus::tomlplusplus)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(${PROJECT_NAME} PUBLIC "src/headers")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB BEDROCK_TESTS tests/*.cpp tests/*.h)

add_executable(${PROJECT_NAME}_test ${BEDROCK_TESTS} ${BEDROCK_HEADERS} ${BEDROCK_SOURCES})

set_target_properties(${PROJECT_NAME}_test
                      PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main tomlplusplus::tomlplusplus)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
