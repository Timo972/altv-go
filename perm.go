package altv

/*
#include <stdlib.h>
#include "capi.h"
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
