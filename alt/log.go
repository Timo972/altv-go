package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import "unsafe"

func LogInfo(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_info(cstr)
}

func LogDebug(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_debug(cstr)
}

func LogWarning(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_warning(cstr)
}

func LogError(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_error(cstr)
}

func LogColored(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	C.core_log_colored(cstr)
}
