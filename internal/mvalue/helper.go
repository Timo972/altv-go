package mvalue

import "C"
import (
	"github.com/timo972/altv-go/internal/pb"
	"google.golang.org/protobuf/proto"
)

func Serialize(protoValue *pb.MValue) ([]byte, error) {
	return proto.Marshal(protoValue)
}

func Encode(v interface{}) (C.struct_array, error) {
	bytes, err := Serialize(New(v))
	if err != nil {
		return C.struct_array{}, err
	}

	ptr := C.CBytes(bytes)
	return C.struct_array{
		array: ptr,
		size:  C.ulonglong(len(bytes)),
	}, nil
}

func EncodeArgs(v []interface{}) (C.struct_array, error) {
	size := len(v)

	if size == 0 {
		return C.struct_array{
			array: nil,
			size:  0,
		}, nil
	}

	ptr := C.malloc(C.size_t(size) * C.size_t(C.sizeof_Array))
	bytesArray := (*[1 << 30]C.struct_array)(ptr)

	for i, arg := range v {
		arr, err := Encode(arg)
		if err != nil {
			return C.struct_array{
				array: nil,
				size:  0,
			}, err
		}

		bytesArray[i] = arr
	}

	return C.struct_array{
		array: ptr,
		size:  C.ulonglong(size),
	}, nil
}
