package alt

import "C"
import (
	"fmt"
	"unsafe"
)

type resource struct {
	Ptr		unsafe.Pointer
	Name	string
	Path	string
}

var Resource resource

func TestResource() {
	fmt.Println("Test Resource")
}

//export initGoResource
func initGoResource(ptr unsafe.Pointer, name *C.char, path *C.char) {
	Resource = resource{Ptr: ptr, Name: C.GoString(name), Path: C.GoString(path)}
}

