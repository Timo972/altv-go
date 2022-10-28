#!/bin/bash

cp ./runtime/bin/libgo-module.so ./test/modules

pushd examples/helloWorld
export CGO_LDFLAGS="-g -ldl"
go build -o ../../test/resources/test/resource.so -buildmode=c-shared
popd

pushd test
./altv-server
popd