# altv-go-pkg [![Build test](https://github.com/shockdev04/altv-go-pkg/actions/workflows/test-changes.yml/badge.svg)](https://github.com/shockdev04/altv-go-pkg/actions/workflows/test-changes.yml)
Go package for alt:V Multiplayer.
Runtime can be found [here](https://github.com/shockdev04/altv-go-module).

## Requirements
Package depends heavily on [cgo](https://pkg.go.dev/cmd/cgo).
To build on Windows, a gcc compiler is required (ex: mingw-w64).

## Usage
Main function is left blank on purpose and must be included before building process. 
Do not try to initialize stuff inside as it won't get called.
```go
package main

import "C"
import "github.com/shockdev04/altv-go-pkg/alt"

func main() { }

//export onStart
func onStart() {
	alt.LogInfo("Resource Started")
}

//export onStop
func onStop() {
	alt.LogInfo("Resource Stopped")
}
```

## Build
#### Windows
```
go build -o my-resource.dll -buildmode=c-shared
```

#### Linux
```
export CGO_LDFLAGS="-g -02 -ldl"
go build -o my-resource.so -buildmode=c-shared
```