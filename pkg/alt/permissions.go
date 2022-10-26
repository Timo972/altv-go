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
import "unsafe"

type Permission = uint8

const (
	PermNone Permission = iota
	PermScreenCapture
	PermWebRTC
	PermClipboardAccess
	PermAll
)

func newPermissionArray(arr C.struct_array) []Permission {
	size := int(arr.size)
	defer C.free(unsafe.Pointer(arr.array))

	cPerms := (*[1 << 28]C.uchar)(arr.array)[:size:size]
	perms := make([]Permission, size)

	for i, p := range cPerms {
		perms[i] = Permission(p)
	}

	return perms
}
