package event

import (
	"unsafe"

	"github.com/timo972/altv-go/entity"
	"github.com/timo972/altv-go/internal/cutil"
	"github.com/timo972/altv-go/mvalue"
)

// #include <stdlib.h>
// #include "capi.h"
import "C"

func marshalArgs(args []any) (C.struct_array, func(), error) {
	cbytearrs := C.malloc(C.size_t(len(args)) * C.size_t(C.sizeof_CArray))
	cargs := C.struct_array{
		ptr:  cbytearrs,
		size: C.ulonglong(len(args)),
	}
	bytearrs := (*[1 << 30]C.struct_array)(cbytearrs)
	free := func() {
		C.free(cbytearrs)

		// TODO: free subarrays?
	}

	for i, arg := range args {
		raw, err := mvalue.Marshal(arg)
		if err != nil {
			free()
			return cargs, nil, err
		}

		bytearrs[i] = C.struct_array{
			ptr:  unsafe.Pointer(C.CBytes(raw)),
			size: C.ulonglong(len(raw)),
		}
	}

	return cargs, free, nil
}

func newPlayerCArray(p []entity.Player) (C.struct_array, cutil.FreeArrayFunc) {
	// 8 is sizeof void ptr on 64bit
	ptr, size, free := cutil.NewCArrayFunc[entity.Player, unsafe.Pointer](p, 8, func(item entity.Player) unsafe.Pointer {
		return item.Ptr()
	})

	return C.struct_array{
			ptr:  ptr,
			size: C.ulonglong(size),
		},
		free
}

// EmitRaw emits an event with the given name and byte data.
func EmitRaw(eventName string, data []byte) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	C.core_trigger_local_event_raw(cEvent, (*C.char)(unsafe.Pointer(&data[0])), C.ulonglong(len(data)))
	return nil
}

func Emit(eventName string, args ...any) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	cargs, free, err := marshalArgs(args)
	if err != nil {
		return err
	}
	defer free()

	C.core_trigger_local_event(cEvent, cargs)

	return nil
}

func EmitClient(p entity.Player, evt string, args ...any) error {
	cevt := C.CString(evt)
	defer C.free(unsafe.Pointer(cevt))

	cargs, free, err := marshalArgs(args)
	if err != nil {
		return err
	}
	defer free()

	C.core_trigger_client_event(p.Ptr(), cevt, cargs)
	return nil
}

func EmitClients(p []entity.Player, evt string, args ...any) error {
	cclients, freeClients := newPlayerCArray(p)
	defer freeClients()

	cevt := C.CString(evt)
	defer C.free(unsafe.Pointer(cevt))

	cargs, freeArgs, err := marshalArgs(args)
	if err != nil {
		return err
	}
	defer freeArgs()

	C.core_trigger_client_event_for(cclients, cevt, cargs)
	return nil
}

func EmitAllClients(evt string, args ...any) error {
	cevt := C.CString(evt)
	defer C.free(unsafe.Pointer(cevt))

	cargs, free, err := marshalArgs(args)
	if err != nil {
		return err
	}
	defer free()

	C.core_trigger_client_event_for_all(cevt, cargs)
	return nil
}
