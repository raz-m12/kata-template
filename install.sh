#!/bin/bash

cd extern
vcpkgDir=./vcpkg

if [ -d "$vcpkgDir" ]; then
    echo "Vcpkg directory already exists"
else
    # Other dependencies
    sudo apt install cmake
    sudo apt install clang
    sudo apt install cppcheck
    sudo apt install clang-tidy
    sudo apt install clang-format
    sudo apt install llvm

    # Install the package manager vcpkg and use it to satisfy
    # the dependencies reported in the manifest file (vcpkg.json)
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics
    ./bootstrap-vcpkg.sh

    # Installs the dependencies system wide
    ./vcpkg integrate install
fi
