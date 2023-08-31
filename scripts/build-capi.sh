#!/bin/bash

go run cmd/gencapi/*.go -cout=./internal/c-api/build/out/capi.c -hout=./internal/c-api/build/out/capi.h -hout=./internal/c-api/lib/capi.h  ./runtime/src/capi

cd ./internal/c-api

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