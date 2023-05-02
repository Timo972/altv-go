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

	var err error
	margs := make([][]byte, len(args))

	for i, arg := range args {
		margs[i], err = mvalue.Marshal(arg)
		if err != nil {
			return err
		}
	}

	return nil
}
