# Create Resource

## Create a project with a Terminal

* Create new folder and run ``go mod init go-resource``
* Run ``go get github.com/shockdev04/altv-go-pkg/alt``

You now have to create a single resource file in your project that is auto initialized on server startup.

main.go
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

## Compile the resource

To compile the resource from the command line use ```go build -o go-resource.dll -buildmode=c-shared``` for windows or 
```bash
export CGO_LDFLAGS="-g -ldl"
go build -o go-resource.so -buildmode=c-shared
```

This will output the resource dll in the root folder.
Copy the dlls to the server resource folder ```altv-server/resources/{YourResourceName}/```.

To get the Resource running on the server, you have to create a "resource.cfg" file.

```
type: go,
main: go-resource.dll
```

Now the resource needs to be added to the server.cfg.

```
resources: [
"{YourResourceName}"
]
```

Your server folder now look similar to this one

```
modules/
└── go-module.dll (libgo-module.so on linux)
resources/
└── my-example-go-resource/
    ├── go-example-resource.dll
    └── resource.cfg
server.cfg
altv-server.exe
```

See how to use [Events](events.md).