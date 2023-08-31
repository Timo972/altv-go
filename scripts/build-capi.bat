@echo off

go run cmd/gencapi/... -cout=./internal/c-api/build/out/capi.c -hout=./internal/c-api/build/out/capi.h -hout=./internal/c-api/lib/capi.h  ./runtime/src/capi

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