package event

// #include "capi.h"
// #include <stdlib.h>
import "C"
import (
	"unsafe"

	"github.com/timo972/altv-go/resource"
)

var queue = map[uint16]struct{}{}

func registerOnEvent(event uint16) {
	if !resource.Ready() {
		queue[event] = struct{}{}
		return
	}

	cresource := C.CString(resource.Current.Name())
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_register_alt_event(cresource, C.ushort(event))
}

func unregisterOnEvent(event uint16) {
	if !resource.Ready() {
		delete(queue, event)
		return
	}

	cresource := C.CString(resource.Current.Name())
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_unregister_alt_event(cresource, C.ushort(event))
}

func processQueue() {
	for event := range queue {
		registerOnEvent(event)
	}
}
