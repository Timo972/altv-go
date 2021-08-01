package alt

import (
	"syscall"
	"unsafe"
)

func LogInfo(msg string) {
	s16, _ := syscall.UTF16PtrFromString(msg)
	GetFunc("Core_LogInfo", uintptr(unsafe.Pointer(s16)))
}
