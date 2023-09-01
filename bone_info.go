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

type BoneInfo struct {
	ID    uint16
	Index uint16
	Name  string
}

func newBoneInfo(info C.struct_boneInfo) BoneInfo {
	return BoneInfo{
		Name:  C.GoString(info.name),
		Index: uint16(info.index),
		ID:    uint16(info.id),
	}
}

func createBoneSlice(arr C.struct_array) []BoneInfo {
	return cutil.NewArrayFunc[C.struct_boneInfo, BoneInfo](unsafe.Pointer(arr.ptr), int(arr.size), func(item C.struct_boneInfo) BoneInfo {
		return newBoneInfo(item)
	})
}
