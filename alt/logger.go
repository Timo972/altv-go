package alt

// #include <stdlib.h>
import "C"
import (
	"github.com/shockdev04/altv-go-pkg/internal/module"
	"unsafe"
)

func LogInfo(msg string) {
	cstr := C.CString(msg)
	defer C.free(unsafe.Pointer(cstr))

	module.GetFunc("Core_LogInfo", uintptr(unsafe.Pointer(cstr)))
}
