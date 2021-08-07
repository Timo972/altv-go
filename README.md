# altv-go-pkg
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
export CGO_LDFLAGS="-g -02 -ldl"
go -o my-resource.dll -buildmode c-shared
```