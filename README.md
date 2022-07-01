# altv-go [![API](https://github.com/timo972/altv-go/actions/workflows/test-api.yml/badge.svg)](https://github.com/timo972/altv-go/actions/workflows/test-api.yml) [![Module](https://github.com/timo972/altv-go/actions/workflows/build-deploy-module.yml/badge.svg)](https://github.com/timo972/altv-go/actions/workflows/build-deploy-module.yml)

Go package for alt:V Multiplayer.
Runtime can be found [here](https://github.com/timo972/altv-go/runtime).

## Requirements

Package depends heavily on [cgo](https://pkg.go.dev/cmd/cgo).
To build on Windows, a gcc compiler is required (ex: mingw-w64).

## Usage

Main function is left blank on purpose and must be included before building process.
Do not try to initialize stuff inside as it won't get called.

```go
package main

import "C"
import "github.com/timo972/altv-go/alt"

func init() {
	// You may want to initialize something here
}

func main() {
	// You dont want to initialize something here because this wont work
}

//export OnStart
func OnStart() {
	alt.LogInfo("Resource Started")
}

//export OnStop
func OnStop() {
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
export CGO_LDFLAGS="-g -ldl"
go build -o my-resource.so -buildmode=c-shared
```
