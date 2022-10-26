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
	defer C.free(unsafe.Pointer(arr.array))
	size := int(arr.size)

	boneArray := (*[1 << 28]C.struct_boneInfo)(arr.array)[:size:size]

	bones := make([]BoneInfo, size)

	if size == 0 {
		return bones
	}

	for i := 0; i < size; i++ {
		bones[i] = newBoneInfo(boneArray[i])
	}

	return bones
}
