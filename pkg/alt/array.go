package alt

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"
import (
	"unsafe"
)

// array converts an array struct to C Value slice
// pointer is free'd afterwards
func convertArray[V any](a C.struct_array) ([]V, int, func()) {
	size := int(a.size)
	cArray := (*[1 << 28]V)(a.array)[:size:size]

	return cArray, size, func() {
		C.free(unsafe.Pointer(a.array))
	}
}

func newStringArray(ptr unsafe.Pointer, size int) []string {
	strings := make([]string, size)
	cStrings := (*[1 << 28]*C.char)(ptr)[:size:size]

	for i, cString := range cStrings {
		strings[i] = C.GoString(cString)
	}

	return strings
}
