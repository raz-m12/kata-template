# Description

This is a c++ project used to practice Test-Driven Development (TDD) using Kata exercises. 

The template includes the boilerplate code intended as a starting point for doing TDD in C++. It uses cmake and the vcpkg package manager to satisfy the dependencies. It is possible to add new dependencies see [branch](TODO_add_branch_link).

Simply create your own branch and get started, there are plenty of example branches showcasing various examples.

# Installation, building and running the tests
Inside the project root run:
```
./install
```
This will configure the package manager vcpkg together with the dependency gtest, the c++ unit testing framework.

From the root directory, to compile and link the project use:
```
cmake .build
cmake --build .build --target kata
```

## Running the tests
From the root directory:
```bash
cd .build
ctest
# or with detailed test output
ctest --rerun-failed --output-on-failure
```

