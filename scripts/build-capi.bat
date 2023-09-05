@echo off

go run ./cmd/gencapi/... -cout=./internal/capi/build/out/capi.c -hout=./internal/capi/build/out/capi.h -hout=./internal/capi/lib/capi.h  ./runtime/src/

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