package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
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

// Console is the default console writer.
var Console io.Writer = &altLog{}

// LogWarning logs a warning message to the console.
func LogWarning(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_warning(cstr)
}

// LogError logs an error message to the console.
func LogError(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_error(cstr)
}

// Log logs a message to the console.
// You can use color codes in the message.
// https://docs.altv.mp/articles/logging.html
func Log(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_colored(cstr)
}
