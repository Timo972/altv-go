#!/bin/bash

go run cmd/gencapi/*.go -cout=./internal/capi/build/out/capi.c -hout=./internal/capi/build/out/capi.h -hout=./internal/capi/lib/capi.h  ./runtime/src/capi

cd ./internal/capi

if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d bin ]; then
    mkdir bin
fi

pushd build

cmake ..
cmake --build .

popd