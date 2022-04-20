package alt

//#include <stdlib.h>
//#include "Module.h"
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

func convertMValueArray(cMValues unsafe.Pointer, cSize C.ulonglong) []interface{} {
	size := uint64(cSize)

	args := make([]interface{}, size)

	cMValueStructs := (*[1 << 30]C.struct_metaData)(cMValues)[:size:size]

	for i := uint64(0); i < size; i++ {
		cMVal := cMValueStructs[i]
		_type := uint8(cMVal.Type)

		mValue := &MValue{Ptr: cMVal.Ptr, Type: _type}

		args[i] = mValue.ReflectValue().Interface()
	}

	return args
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
