mkdir extern
cd extern
git clone https://github.com/microsoft/vcpkg
cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics
./bootstrap-vcpkg.sh
./vcpkg integrate install
