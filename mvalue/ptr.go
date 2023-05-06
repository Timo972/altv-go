package mvalue

import (
	"strconv"
	"unsafe"
)

// ParsePointer parses an unsafe.Pointer from a string.
func ParsePointer(ptrStr string) (unsafe.Pointer, error) {
	if ptrStr == "" {
		// return nil pointer
		return nil, nil
	}

	ptrUint, err := strconv.ParseUint(ptrStr, 10, 64)
	if err != nil {
		return nil, err
	}

	return unsafe.Pointer(uintptr(ptrUint)), nil
}
