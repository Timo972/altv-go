package imprt

import (
	"unsafe"

	"github.com/timo972/altv-go/mvalue"
)

// #cgo CFLAGS: -I../internal/capi/lib
// #cgo linux LDFLAGS: -L../internal/capi/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/capi/lib/win32 -lcapi -ldl -g
// #cgo darwin LDFLAGS: -L../internal/capi/lib/darwin -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"

func resourceImport(resourceName string, name string, out any) error {
	crname := C.CString(resourceName)
	defer C.free(unsafe.Pointer(crname))

	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))

	carr := C.runtime_get_alt_export(crname, cname)
	data := C.GoBytes(carr.ptr, C.int(carr.size))

	return mvalue.Unmarshal(data, out)
}

// New imports a value exported by another resource, no matter which language. See mvalue serialization for more information about supported values.
func New(resourceName string, name string, out any) error {
	return resourceImport(resourceName, name, out)
}
