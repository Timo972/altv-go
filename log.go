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

var Console io.Writer = &altLog{}

func LogWarning(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_warning(cstr)
}

func LogError(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_error(cstr)
}

func Log(msgs ...string) {
	cstr := C.CString(strings.Join(msgs, " "))
	defer C.free(unsafe.Pointer(cstr))
	C.core_log_colored(cstr)
}
