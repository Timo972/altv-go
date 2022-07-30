@echo off
IF NOT EXIST build\ (
    mkdir build
)

IF NOT EXIST bin\ (
    mkdir bin
)
pushd build
cmake -G"Visual Studio 16" -A x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build . --config Release
popd
