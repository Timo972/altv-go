package events

import (
	"unsafe"

	"github.com/timo972/altv-go/mvalue"
)

// #include <stdlib.h>
// #include "capi.h"
import "C"

// EmitRaw emits an event with the given name and byte data.
func EmitRaw(eventName string, data []byte) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	C.core_trigger_local_event_raw(cEvent, (*C.char)(unsafe.Pointer(&data[0])), C.ulonglong(len(data)))
	return nil
}

func Emit(eventName string, args ...interface{}) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	cbytearrs := C.malloc(C.size_t(len(args)) * C.size_t(C.sizeof_Array))
	cargs := C.struct_array{
		array: cbytearrs,
		size:  C.ulonglong(len(args)),
	}
	bytearrs := (*[1 << 30]C.struct_array)(cbytearrs)
	defer C.free(cbytearrs)

	for i, arg := range args {
		raw, err := mvalue.Marshal(arg)
		if err != nil {
			return err
		}

		bytearrs[i] = C.struct_array{
			array: unsafe.Pointer(C.CBytes(raw)),
			size:  C.ulonglong(len(raw)),
		}
	}

	C.core_trigger_local_event(cEvent, cargs)

	return nil
}
