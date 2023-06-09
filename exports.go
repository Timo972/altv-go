package altv

import (
	"errors"
	"unsafe"

	"github.com/timo972/altv-go/mvalue"
)

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"

var ErrFailedToRegisterExport = errors.New("failed to register export")

func resourceImport(resourceName string, name string, out any) error {
	crname := C.CString(resourceName)
	defer C.free(unsafe.Pointer(crname))

	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))

	carr := C.runtime_get_alt_export(crname, cname)
	data := C.GoBytes(carr.array, C.int(carr.size))

	return mvalue.Unmarshal(data, out)
}

// Export exports a value which can be imported by other resources, no matter which language. See mvalue serialization for more information about supported values.
func Export(name string, value any) error {
	carr, free, err := marshal(value)
	if err != nil {
		return err
	}
	defer free()

	crname := C.CString(CurrentResource.Name())
	defer C.free(unsafe.Pointer(crname))

	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))

	ok := C.runtime_register_alt_export(crname, cname, carr)

	if int(ok) != 1 {
		return ErrFailedToRegisterExport
	}

	return nil
}

// Import imports a value exported by another resource, no matter which language. See mvalue serialization for more information about supported values.
func Import(resourceName string, name string, out any) error {
	return resourceImport(resourceName, name, out)
}
