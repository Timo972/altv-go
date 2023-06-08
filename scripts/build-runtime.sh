#!/bin/bash
cd runtime

if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d bin ]; then
    mkdir bin
fi

pushd build

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ ..
cmake --build . --config Release

popd
