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
  <a href="/TROUBLESHOOTING.md">Troubleshooting</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="/CONTRIBUTING.md">Contributing</a>
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

<!-- > ⚠️ notice: i am too busy to keep this module updated even though no one is interested in it / using it.
> Create an issue or write me on Discord if you are interested or plan on using it, so i will continue updating / improving.
-->

> ⚠️ Notice: updated occasionally, not actively maintained  
> ⛔ Module is currently in development and not ready for production use - expect heavy api changes and bugs.  
> ✨ Contributions of any kind are always welcome!

## Requirements

Package depends heavily on [cgo](https://pkg.go.dev/cmd/cgo).
To build on Windows, a gcc compiler is required (ex: mingw-w64).

## Usage

Main function is left blank on purpose and must be included before building process.
Do not try to initialize stuff inside as it won't get called.

```go
package main

import "C"
import (
  "github.com/timo972/altv-go"
  // this package is a required import. if you are not using the event package, import it like this
  // _ "github.com/timo972/altv-go/event"
  // if you are not importing it, the module will log errors calling the ServerStarted and ResourceStopEvent
	"github.com/timo972/altv-go/event"
)

func init() {
	// You may want to initialize something here.
  // However the alt:V api is limited due to the reason
  // that the package did not load the go-module's c-api yet!
  // As of now you can only use the event features here.

  // e.g.
  event.On.ServerStarted(func () {
      altv.LogInfo("Server Started")
    })
}

// main function is left blank on purpose and must be included before building process
func main() {
	// You dont want to initialize something here because this wont work
}

//export OnStart
func OnStart() {
  // Full alt:V api is available. Do whatever you want.

	altv.LogInfo("Resource Started")
}

//export OnStop
func OnStop() {
	altv.LogInfo("Resource Stopped")
}
```

For more examples take a look at the [altv-go-examples]() repository.

## Building your Resource

#### Windows

```
go build -o my-resource.dll -buildmode=c-shared
```

#### Linux

```
go build -o my-resource.so -buildmode=c-shared
```

Something went wrong? A build error? See the [Troubleshooting Guide](/TROUBLESHOOTING.md).

## Help

If you need help to get started contact me on Discord: `Timo9#4468`
