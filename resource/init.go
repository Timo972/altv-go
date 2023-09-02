package resource

import (
	"fmt"
	"log"
	"unsafe"

	"github.com/timo972/altv-go/internal/lib"
)

// #include <stdlib.h>
// #include "capi.h"
import "C"

var ready = false

// var sig = make(chan os.Signal, 1)

/*func init() {
	// signal.Notify(sig)
}*/

/*func handleSignal(signal os.Signal) {
	if signal == syscall.SIGKILL || signal == syscall.SIGTERM || signal == syscall.SIGINT {
		StopServer()
		return
	}

	fmt.Printf("received signal: %s\n", signal)
}

func listenSignal() {
	for {
		s := <-sig
		handleSignal(s)
	}
}*/

var current *Local

//export initGoResource
func initGoResource(ptr unsafe.Pointer, name *C.char, path *C.char, ver *C.char) C.int {
	fmt.Println("resource initializing")

	current = &Local{
		name: C.GoString(name),
		path: C.GoString(path),
		Public: Public{
			ptr: ptr,
		},
	}
	C.GoString(ver)

	mod := C.CString(lib.MODULE_NAME)
	defer C.free(unsafe.Pointer(mod))

	log.SetFlags(log.Ltime)

	fmt.Printf("resource loading module %s\n", lib.MODULE_NAME)

	status := C.load_module(mod)
	if int(status) == 0 {
		log.Printf("couldn't locate %s library", lib.MODULE_NAME)
		return status
	}

	fmt.Println("resource initialized")

	ready = true

	// go listenSignal()

	return status
}

func Ready() bool {
	return ready
}

// Current returns the local resource you are scripting in. returns nil until resource is initialized
func Current() *Local {
	return current
}
