package module

// #include <stdlib.h>
import "C"
import "unsafe"

func RegisterAltEvent(resource string, event uint16) {
	cresource := C.CString(resource)
	defer C.free(unsafe.Pointer(cresource))

	GetFunc("RegisterAltEvent", uintptr(unsafe.Pointer(cresource)), C.uint(event))
}
