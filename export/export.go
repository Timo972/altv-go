package export

import (
	"errors"
)

// #cgo CFLAGS: -I../internal/capi/lib
// #cgo linux LDFLAGS: -L../internal/capi/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/capi/lib/win32 -lcapi -ldl -g
// #cgo darwin LDFLAGS: -L../internal/capi/lib/darwin -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"

var ErrFailedToRegister = errors.New("failed to register export")

// Export exports a value which can be imported by other resources, no matter which language. See mvalue serialization for more information about supported values.
func New(name string, value any) error {
	/*carr, free, err := marshal(value)
	if err != nil {
		return err
	}
	defer free()

	crname := C.CString(resource.Current.Name())
	defer C.free(unsafe.Pointer(crname))

	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))

	ok := C.runtime_register_alt_export(crname, cname, carr)

	if int(ok) != 1 {
		return ErrFailedToRegister
	}*/

	return nil
}
