# Enables the vcpkg toolchain allowing to install gtest and any
# other dependencies specified in vcpkg.json, used with ./install
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

cmake_minimum_required (VERSION 3.21)
project (kata_exercise)

# Compiler configurable options, uses the c++2020 standard
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -g -std=c++2a")

# Creates the executable with source files
set (SRCS 
    src/main.cpp
    src/ArgsParser.cpp
    test/ArgsParserTest.cpp)
add_executable(kata ${SRCS})

# Enables header imports via #include "include/header.hpp"
set(header_files
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_include_directories(kata PRIVATE ${header_files})

# Allows to add further dependencies based on external 
# libraries tools installed via vcpkg.
find_package(GTest CONFIG REQUIRED)
target_link_libraries(kata PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

# Allows to use ctest inside the .build directory. However,
# generally this doesn't be used. Use vs code TestMate support.
enable_testing()
add_test(Unit kata)
