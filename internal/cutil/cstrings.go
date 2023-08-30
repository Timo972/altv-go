package cutil

import "unsafe"
import "C"

func NewStringArray(ptr unsafe.Pointer, size int) []string {
	strings := make([]string, size)
	cStrings := (*[1 << 28]*C.char)(ptr)[:size:size]

	for i, cString := range cStrings {
		strings[i] = C.GoString(cString)
	}

	return strings
}
