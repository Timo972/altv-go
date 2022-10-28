@echo off

cd.\internal\c-api

IF NOT EXIST build\ (
    mkdir build
)

IF NOT EXIST lib\ (
    mkdir lib
)

pushd build
cmake -G"MinGW Makefiles" ..
cmake --build . --config=Release
popd