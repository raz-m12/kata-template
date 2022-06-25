#!/bin/bash

cd extern
vcpkgDir=./vcpkg

if [ -d "$vcpkgDir" ]; then
   echo "Vcpkg directory already exists"
else
   # Install the package manager vcpkg and use it to satisfy
   # the dependencies reported in the manifest file (vcpkg.json)
   git clone https://github.com/microsoft/vcpkg
   cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics
   ./bootstrap-vcpkg.sh

   # Installs the dependencies system wide
   ./vcpkg integrate install
fi
