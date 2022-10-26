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

type PedModelInfo struct {
	Name  string
	Hash  uint32
	Bones []BoneInfo
}

func newPedModelInfo(info C.struct_pedModelInfo) PedModelInfo {
	return PedModelInfo{
		Name:  C.GoString(info.name),
		Hash:  uint32(info.hash),
		Bones: createBoneSlice(info.bones),
	}
}
