package main

import "github.com/timo972/altv-go/pkg/alt"

func main() {}

//export OnStart
func OnStart() {
	alt.LogInfo("Hello World")
}

//export OnStop
func OnStop() {
	alt.LogInfo("Bye World")
}
