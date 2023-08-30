package cutil

/*
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"
)

// NewArray casts a c arr ptr & size to a slice.
// dont free pointer until slice is no longer used.
func NewArray[V any](ptr unsafe.Pointer, size int) ([]V, func()) {
	cArray := (*[1 << 28]V)(ptr)[:size:size]

	return cArray, func() {
		C.free(ptr)
	}
}

func NewArrayFunc[ArrayValue any, TargetValue any](ptr unsafe.Pointer, size int, convert func(item ArrayValue) TargetValue) []TargetValue {
	arr, free := NewArray[ArrayValue](ptr, size)
	defer free()

	slice := make([]TargetValue, size)
	for i, item := range arr {
		slice[i] = convert(item)
	}

	return slice
}

type FreeArrayFunc func()

func NewCArrayFunc[ArrayType any, TargetType any](values []ArrayType, vsizet int, convert func(item ArrayType) TargetType) (unsafe.Pointer, int, FreeArrayFunc) {
	size := len(values)
	ptr := C.malloc(C.size_t(size) * C.size_t(vsizet))
	arr := (*[1 << 30]TargetType)(ptr)

	for i := 0; i < size; i++ {
		arr[i] = convert(values[i])
	}

	return ptr, size, func() {
		C.free(ptr)
	}
}
