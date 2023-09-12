package altlog

// #cgo CFLAGS: -I../internal/capi/lib
// #cgo linux LDFLAGS: -L../internal/capi/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/capi/lib/win32 -lcapi -ldl -g
// #cgo darwin LDFLAGS: -L../internal/capi/lib/darwin -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"
import (
	"io"
	"strings"
	"unsafe"
)

type altLog struct {
}

func (l *altLog) Write(p []byte) (n int, err error) {
	cstr := C.CString(string(p))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_info(cstr)
	return len(p), nil
}

// Stdout is the default console writer.
var Stdout io.Writer = &altLog{}

// LogWarning logs a warning message to the console.
func Warnln(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_warning(cstr)
}

// LogError logs an error message to the console.
func Errorln(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_error(cstr)
}

// Log logs a message to the console.
// You can use color codes in the message.
// https://docs.altv.mp/articles/logging.html
func Println(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_colored(cstr)
}
