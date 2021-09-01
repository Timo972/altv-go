package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
	"encoding/json"
	"unsafe"
)

func stringify(args []interface{}) string {
	str := ""
	for i, arg := range args {
		if i > 0 {
			str += " "
		}
		msg, ok := arg.(string)
		if ok {
			str += msg
			continue
		}
		data, err := json.Marshal(arg)
		if err != nil {
			str += "{}"
		} else {
			str += string(data)
		}
	}
	return str
}

func LogInfo(args...interface{}) {
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
