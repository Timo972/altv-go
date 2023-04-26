package altv

import (
	"io"
	"strings"
	"unsafe"
)

// #include <stdlib.h>
// #include "capi.h"
import "C"

// FileExists checks if the file at the given path exists.
func FileExists(path string) bool {
	cStr := C.CString(path)
	defer C.free(unsafe.Pointer(cStr))

	return int(C.core_file_exists(cStr)) == 1
}

// FileReadAll reads the file at the given path and returns its content as a string.
func FileReadAll(path string) (string, error) {
	cStr := C.CString(path)
	defer C.free(unsafe.Pointer(cStr))

	cContent := C.core_read_file(cStr)
	return C.GoString(cContent), nil
}

// FileRead reads the file at the given path and returns an io.Reader.
func FileRead(path string) (io.Reader, error) {
	data, err := FileReadAll(path)
	if err != nil {
		return nil, err
	}

	return strings.NewReader(data), nil
}
