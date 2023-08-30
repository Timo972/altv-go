package altv

import (
	"fmt"
	"log"
	"unsafe"

	"github.com/timo972/altv-go/internal/lib"
	"github.com/timo972/altv-go/mvalue"
)

// #cgo CFLAGS: -I./internal/c-api/lib
// #cgo linux LDFLAGS: -L./internal/c-api/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L./internal/c-api/lib/win32 -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
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

//export initGoResource
func initGoResource(ptr unsafe.Pointer, name *C.char, path *C.char, ver *C.char) C.int {
	fmt.Println("resource initializing")

	CurrentResource = &localResource{
		name: C.GoString(name),
		path: C.GoString(path),
		publicResource: publicResource{
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
		log.Fatalf("couldn't locate %s library", lib.MODULE_NAME)
	}

	fmt.Println("resource initialized")

	mvalue.SetResourceName(CurrentResource.Name())

	ready = true

	// go listenSignal()

	return status
}

func Ready() bool {
	return ready
}
