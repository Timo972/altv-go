<div align="center">
  <h1>alt:V Go</h1>
  <a href="https://github.com/timo972/altv-go/actions/workflows/test-api.yml">
    <img src="https://github.com/timo972/altv-go/actions/workflows/test-api.yml/badge.svg" />
  </a>
  <a href="https://github.com/Timo972/altv-go/actions/workflows/test-module.yml">
    <img src="https://github.com/Timo972/altv-go/actions/workflows/test-module.yml/badge.svg" />
  </a>
  <a href="https://github.com/timo972/altv-go/actions/workflows/publish-module.yml">
    <img src="https://github.com/timo972/altv-go/actions/workflows/publish-module.yml/badge.svg" />
  </a>
  <a href="https://github.com/edgedb/edgedb/blob/master/LICENSE">
    <img alt="license" src="https://img.shields.io/badge/license-MIT-blue" />
  </a>
  <br />
  <br />
	
  [Documentation]
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  [Troubleshooting]
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  [Contributing]
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://altv.mp">alt:V</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://discord.altv.mp">Discord</a>
  <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
  <a href="https://twitter.com/altVMP">Twitter</a>
  <br />

</div>
<br />

Go package and runtime for alt:V Multiplayer.

<!-- > ⚠️ notice: i am too busy to keep this module updated even though no one is interested in it / using it.
> Create an issue or write me on Discord if you are interested or plan on using it, so i will continue updating / improving.
-->

> ⚠️ Notice: updated occasionally, not actively maintained - hit me up on Discord if you are interested in this project.<br />
> ⛔ Module is currently in development and not ready for production use - expect heavy api changes (and bugs).<br />
> ✨ [Contributions][Contributing] of any kind are always welcome!<br />

## Requirements

Package depends heavily on [cgo](https://pkg.go.dev/cmd/cgo).
To build on Windows, a gcc compiler is required (ex: mingw-w64).<br />
See our [Requirements Guide][Requirements] for more information on requirements and how to install them.

## Get started

Main function is left blank on purpose and must be included before building process.
Do not try to initialize stuff inside as it won't get called.

```go
package main

import "C"
import (
  "github.com/timo972/altv-go/altlog"
  // the altv-go/event package is a required import. if you are not using it, do a sideeffect import
  // if you are not importing it, the module will log errors calling the ServerStarted and ResourceStopEvent
  // either do (when using events)
  "github.com/timo972/altv-go/event"
  // or (when not using events)
  // _ "github.com/timo972/altv-go/event"
)

func init() {
  // You may want to initialize something here.
  // However the alt:V api is limited due to the reason
  // that the package did not load the go-module's c-api yet!
  // As of now you can only use the event features here.
  // Full api is available once the event.on.Start callbacks are executed.

  // e.g.
  event.On.ServerStarted(func () {
      altlog.Println("Server Started")
  })

  event.On.Start(func () {
    // this event is called when the resource is being started by the alt:V Core
    // full api available
    altlog.Println("Resource Started")
  })

  event.On.Stop(func () {
    // this event is called when on resource shutdown
    altlog.Println("Resource Stopped")
  })
}

// main function is left blank on purpose and must be included before building process
func main() {
  // You dont want to initialize something here because this wont work
}
```

For more examples reach out to [me at Discord][Maintainer].

## Building your Resource

### Windows

```
go build -o my-resource.dll -buildmode=c-shared
```

### Linux

```
go build -o my-resource.so -buildmode=c-shared
```

Something went wrong? A build error? See the [Troubleshooting Guide][Troubleshooting].

## Help

If you need help to get started contact me on [Discord: `Timo9#4468`][Maintainer]

[Contributing]: https://github.com/timo972/altv-go/wiki/Contributing
[Troubleshooting]: https://github.com/timo972/altv-go/wiki/Troubleshooting
[Requirements]: https://github.com/timo972/altv-go/wiki/Requirements
[Documentation]: https://github.com/Timo972/altv-go/wiki
[Maintainer]: https://discord.com/users/262702731309875200
