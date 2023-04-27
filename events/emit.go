package events

import "unsafe"

// #include <stdlib.h>
// #include "capi.h"
import "C"

// Emit emits an event with the given name and byte data.
func EmitRaw(eventName string, data []byte) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	C.core_trigger_local_event_raw(cEvent, (*C.char)(unsafe.Pointer(&data[0])), C.ulonglong(len(data)))
	return nil
}
