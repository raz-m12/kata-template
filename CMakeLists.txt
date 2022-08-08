# Enables the vcpkg toolchain allowing to install gtest and any
# other dependencies specified in vcpkg.json, used with ./install
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

cmake_minimum_required (VERSION 3.21)

# Can change to another compiler like g++ or gcc (see tasks.json)
# set(CMAKE_CXX_COMPILER "clang++")

# Enable linters
# Clang Tidy linter (see target Run Clang Tidy)
option(MyOption "RUN_CLANG_TIDY" OFF)

if(RUN_CLANG_TIDY)
   message("Running clang tidy")
   set(CMAKE_CXX_CLANG_TIDY
      clang-tidy;
      -header-filter=.;
      -checks=*;)
endif()

# Compiler configurable options, uses the c++2020 standard
# Passing -Wextra uses a linter as well
# Adds compile time optimizations -O3
# Adds link time optimizations -flto
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -Wextra -g -std=c++2a")

# CppCheck linter (must be installed to be used by the flylint extension)
# Generates a file used by the target "Run CppCheck static analyser".
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (kata_exercise)

# Creates the executable with source files
set (SRCS 
    src/main.cpp
    src/ArgumentParser.cpp
    test/ArgumentParserTest.cpp)
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
