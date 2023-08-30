package cstrings

import "unsafe"
import "C"

func NewArray(ptr unsafe.Pointer, size int) []string {
	strings := make([]string, size)
	cStrings := (*[1 << 28]*C.char)(ptr)[:size:size]

	for i, cString := range cStrings {
		strings[i] = C.GoString(cString)
	}

	return strings
}
