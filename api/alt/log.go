package alt

/*
#cgo windows CFLAGS: -I../../c-api/lib
#cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi

#cgo linux CFLAGS: -I../../c-api/lib
#cgo linux LDFLAGS: -g -L../../c-api/lib/linux -lcapi  -ldl

#ifndef GOLANG_APP
#define GOLANG_APP

#include <stdlib.h>
#include "capi.h"

#endif
*/
import "C"
import (
	"encoding/json"
	"strings"
	"unsafe"
)

type loggableStruct interface {
	String() string
}

func stringify(args []interface{}) string {
	messages := make([]string, len(args))
	for i, arg := range args {

		// if the argument is a string, just append it
		if msg, ok := arg.(string); ok {
			messages[i] = msg
			continue
		}

		// if the argument is a loggable struct, call its String() method
		if loggable, ok := arg.(loggableStruct); ok {
			messages[i] = loggable.String()
			continue
		}

		// otherwise, serialize it to JSON
		if data, err := json.Marshal(arg); err != nil {
			messages[i] = err.Error()
		} else {
			messages[i] = string(data)
		}
	}

	return strings.Join(messages, " ")
}

func LogInfo(args ...interface{}) {
	msg := stringify(args)
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_info(cstr)
}

func LogDebug(args ...interface{}) {
	msg := stringify(args)
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_debug(cstr)
}

func LogWarning(args ...interface{}) {
	msg := stringify(args)
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_warning(cstr)
}

func LogError(args ...interface{}) {
	msg := stringify(args)
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_error(cstr)
}

func LogColored(args ...interface{}) {
	msg := stringify(args)
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_colored(cstr)
}
