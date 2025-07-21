cmake_minimum_required(VERSION 3.16)
project(json_parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------------
# Main Library
# ----------------------------------------------------------------------------
add_library(json_parser STATIC
    json_parser.cpp
    json_parser.h
)
target_include_directories(json_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# GoogleTest Setup (fetch if not available)
# ----------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ----------------------------------------------------------------------------
# Test Executable
# ----------------------------------------------------------------------------
file(GLOB_RECURSE TEST_SOURCES
    tests/unit/*.cpp
    tests/main.cpp
)

add_executable(json_parser_tests ${TEST_SOURCES})

target_link_libraries(json_parser_tests
    PRIVATE
        gtest_main
        json_parser
)

target_include_directories(json_parser_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(json_parser_tests)
