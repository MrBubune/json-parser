cmake_minimum_required(VERSION 3.14)
project(json_parser)

# Enable C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header directory
include_directories(include)

# Create the core library
add_library(json_parser
    src/json_parser.cpp
)

# Add GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the test executable
add_executable(json_parser_tests
    tests/test_parse_primitives.cpp
    # add more test files here
)

target_link_libraries(json_parser_tests
    json_parser
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(json_parser_tests)
