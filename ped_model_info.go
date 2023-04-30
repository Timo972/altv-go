package altv

/*
#include <stdlib.h>
#include "capi.h"
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
