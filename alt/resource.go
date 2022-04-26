package alt

// #cgo windows CFLAGS: -I../c-api/lib/win32
// #cgo windows LDFLAGS: -L../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../c-api/lib/linux
// #cgo linux LDFLAGS: -L../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"log"
	"unsafe"
)

type resource struct {
	Ptr  unsafe.Pointer
	Name string
	Path string
}

var Resource *resource

//export initGoResource
func initGoResource(ptr unsafe.Pointer, name *C.char, path *C.char) {
	Resource = &resource{Ptr: ptr, Name: C.GoString(name), Path: C.GoString(path)}

	cstr := C.CString("go-module")
	defer C.free(unsafe.Pointer(cstr))

	log.SetFlags(log.Ltime)

	moduleLoaded := int(C.load_module(cstr))
	if moduleLoaded == 0 {
		log.Fatal("Couldn't locate go-module library.")
	}
}
