#!/bin/bash

cd ./c-api

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