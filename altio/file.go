package altio

// #cgo CFLAGS: -I../internal/capi/lib
// #cgo linux LDFLAGS: -L../internal/capi/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/capi/lib/win32 -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"
import (
	"io"
	"strings"
	"unsafe"
)

// FileExists checks if the file at the given path exists.
func Exists(path string) bool {
	cStr := C.CString(path)
	defer C.free(unsafe.Pointer(cStr))

	return int(C.core_file_exists(cStr)) == 1
}

// ReadAll reads the file at the given path and returns its content as a string.
func ReadAll(path string) (string, error) {
	cStr := C.CString(path)
	defer C.free(unsafe.Pointer(cStr))

	cContent := C.core_read_file(cStr)
	return C.GoString(cContent), nil
}

// Read reads the file at the given path and returns an io.Reader.
func Read(path string) (io.Reader, error) {
	data, err := ReadAll(path)
	if err != nil {
		return nil, err
	}

	return strings.NewReader(data), nil
}
