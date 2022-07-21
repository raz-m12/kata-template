# Description

This is a c++ project used to practice Test-Driven Development (TDD) using Kata exercises. 

The template includes boilerplate code intended as a starting point for doing TDD in C++. It uses cmake for build automation and vcpkg to satisfy dependencies.

## Dependencies
### Necessary
* clang version 10.0.0
* cmake version 3.21.4
### Optional:
* c++ linters (with vs code support): clang-tidy and cppcheck
* clang-format
### Vengono installati in automatico:
* vcpkg (package management program)
* gtest/gmock (downloaded via vcpkg)

# Installation, building and running the tests
Inside the project root run:
```
./install.sh
```
This will configure the package manager vcpkg together with the dependency gtest, the c++ unit testing framework.

From the root directory, to compile and link the project use:
```
cd .build && cmake ..
cmake --build . --target kata
```

## Running the tests
From the root directory:
```bash
# From the .build directory
./kata
# or with detailed test output
ctest --rerun-failed --output-on-failure
```
