package alt

// #cgo CFLAGS: -I../c-api/lib
// #cgo LDFLAGS: -L../c-api/lib -lcapi
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
