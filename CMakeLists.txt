# Enables the vcpkg toolchain allowing to install gtest and any
# other dependencies specified in vcpkg.json, used with ./install
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

cmake_minimum_required (VERSION 3.14)

project (kata_exercise)

find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -g -std=c++2a")

set (SRCS 
	src/main.cpp
    test/ChristmasLightsKataTest.cpp)

add_executable(kata ${SRCS})

target_link_libraries(kata PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_test(test_all kata)