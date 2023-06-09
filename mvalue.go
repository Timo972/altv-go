package altv

import (
	"unsafe"

	"github.com/timo972/altv-go/mvalue"
)

// #include "capi.h"
// #include <stdlib.h>
import "C"

func marshal(v any) (C.struct_array, func(), error) {
	data := C.struct_array{}
	raw, err := mvalue.Marshal(v)
	if err != nil {
		return data, nil, err
	}

	data.array = unsafe.Pointer(C.CBytes(raw))
	data.size = C.ulonglong(len(raw))

	return data, func() {
		C.free(data.array)
	}, nil
}

func unmarshal(data C.struct_array, v any) error {
	raw := C.GoBytes(data.array, C.int(data.size))

	return mvalue.Unmarshal(raw, v)
}
