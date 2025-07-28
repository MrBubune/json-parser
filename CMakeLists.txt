cmake_minimum_required(VERSION 3.14)
project(json_parser VERSION 1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force MSVC to use dynamic runtime (/MD /MDd)
if(MSVC)
    message(STATUS "Forcing MSVC to use DLL runtime...")
    foreach(flag 
        CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG 
        CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE 
        CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_RELWITHDEBINFO 
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_MINSIZEREL)
        string(REPLACE "/MT" "/MD" ${flag} "${${flag}}")
    endforeach()
endif()

# Add the library
add_library(json_parser
    src/json_parser/json_parser.cpp
)

# Include public headers
target_include_directories(json_parser
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Create alias target for easier usage (optional)
add_library(JsonParser::JsonParser ALIAS json_parser)

# ------------------ Testing Setup ------------------

enable_testing()

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Ensure gtest uses /MD

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(json_parser_tests
    tests/test_main.cpp
    tests/unit/test_parse_primitives.cpp
    tests/unit/test_parse_objects.cpp
    tests/unit/test_key_value_parsing.cpp
    tests/unit/test_parse_strings.cpp
    tests/unit/test_parse_booleans_and_null.cpp
    tests/unit/test_parse_array.cpp
)

# Link test executable with GTest and your library
target_link_libraries(json_parser_tests
    PRIVATE
        json_parser
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(json_parser_tests)

# ------------------ Installation ------------------

include(GNUInstallDirs)

install(TARGETS json_parser
    EXPORT json_parser_targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/json_parser
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT json_parser_targets
    NAMESPACE JsonParser::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/json_parser
)

# ------------------ Export Config ------------------

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/json_parserConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/json_parserConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/json_parserConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/json_parser
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/json_parserConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/json_parserConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/json_parser
)
