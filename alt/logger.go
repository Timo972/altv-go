package alt

// #include <stdlib.h>
import "C"
import (
	"unsafe"
)

func LogInfo(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	GetFunc("Core_LogInfo", uintptr(unsafe.Pointer(cstr)))
}
