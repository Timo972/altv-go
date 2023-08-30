package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"
import (
	"unsafe"

	"github.com/timo972/altv-go/internal/cutil"
)

type Permission = uint8

const (
	PermNone Permission = iota
	PermScreenCapture
	PermWebRTC
	PermClipboardAccess
	PermAll
)

func newPermissionArray(arr C.struct_array) []Permission {
	return cutil.NewArrayFunc[C.uchar, Permission](unsafe.Pointer(arr.array), int(arr.size), func(item C.uchar) Permission {
		return Permission(item)
	})
}
