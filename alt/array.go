package alt

// #cgo windows CFLAGS: -I../c-api/lib/win32
// #cgo windows LDFLAGS: -L../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../c-api/lib/linux
// #cgo linux LDFLAGS: -L../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"unsafe"
)

// array converts an array struct to C Value slice
// pointer is free'd afterwards
func convertArray[V any](a C.struct_array) ([]V, int) {
	size := int(a.size)
	// FIXME: may causes a crash because it frees to early
	defer C.free(unsafe.Pointer(a.array))

	cArray := (*[1 << 28]V)(a.array)[:size:size]

	return cArray, size
}

func newStringArray(ptr unsafe.Pointer, size int) []string {
	strings := make([]string, size)
	cStrings := (*[1 << 28]*C.char)(ptr)[:size:size]

	// for i := 0; i < size; i++ {
	// 	strings[i] = C.GoString(cStrings[i])
	// }

	for i, cString := range cStrings {
		strings[i] = C.GoString(cString)
	}

	return strings
}
