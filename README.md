<div align="center">
  <h1>alt:V Go</h1>
  <a href="https://github.com/timo972/altv-go/actions/workflows/test-api.yml">
    <img src="https://github.com/timo972/altv-go/actions/workflows/test-api.yml/badge.svg" />
  </a>
	<a href="https://github.com/Timo972/altv-go/actions/workflows/test-module.yml">
    <img src="https://github.com/Timo972/altv-go/actions/workflows/test-module.yml/badge.svg" />
  </a>
	<a href="https://github.com/timo972/altv-go/actions/workflows/build-deploy-module.yml">
    <img src="https://github.com/timo972/altv-go/actions/workflows/build-deploy-module.yml/badge.svg" />
  </a>
  <a href="https://github.com/edgedb/edgedb/blob/master/LICENSE">
    <img alt="license" src="https://img.shields.io/badge/license-MIT-blue" />
  </a>
  <br />
  <br />
  <a href="https://altv-go.tbeck.dev/guide/get-started">Get started</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://altv-go.tbeck.dev">Docs</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://altv.mp">alt:V</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://discord.altv.mp">Discord</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://twitter.com/altVMP">Twitter</a>
  <br />

</div>
<br />

> Go package for alt:V Multiplayer. Runtime can be found [here](runtime).

## Requirements

Package depends heavily on [cgo](https://pkg.go.dev/cmd/cgo).
To build on Windows, a gcc compiler is required (ex: mingw-w64).

## Usage

Main function is left blank on purpose and must be included before building process.
Do not try to initialize stuff inside as it won't get called.

```go
package main

import "C"
import "github.com/timo972/altv-go/api/alt"

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

#### Linux (currently broken)

```
export CGO_LDFLAGS="-g -ldl"
go build -o my-resource.so -buildmode=c-shared
```
