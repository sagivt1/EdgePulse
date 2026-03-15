cmake_minimum_required(VERSION 3.22.1)

project(EdgePulse VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find the dependencies Conan generated
find_package(spdlog REQUIRED)
find_package(SQLiteCpp REQUIRED)

# Define the source files for the project
set(SOURCES
    src/main.cpp
    src/core/Logger.cpp
    src/persistence/SQLiteTelemetryRepository.cpp
)

# Create the main executable using the specified sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the spdlog library to the main executable
# Fixed typo: targt_link_libraries -> target_link_libraries
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog SQLiteCpp)

# Enable testing capabilities (CTest)
enable_testing()
find_package(GTest REQUIRED)

# Create the unit test executable
add_executable(unit_tests
    tests/test_exceptions.cpp
    tests/test_persistence.cpp
    src/core/Logger.cpp
    src/persistence/SQLiteTelemetryRepository.cpp
)

# Link GTest and spdlog to the test executable
# Fixed target name: unit_test -> unit_tests
target_link_libraries(unit_tests PRIVATE GTest::gtest_main spdlog::spdlog SQLiteCpp)

include(GoogleTest)
# Discover tests so they appear in CTest
gtest_discover_tests(unit_tests)
