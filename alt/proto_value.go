package alt

// #cgo windows CFLAGS: -I../c-api/lib/win32
// #cgo windows LDFLAGS: -L../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../c-api/lib/linux
// #cgo linux LDFLAGS: -L../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"fmt"
	"reflect"

	"github.com/timo972/altv-go-pkg/internal/pb"
	"google.golang.org/protobuf/proto"
)

func newProtoMValue(value interface{}) *pb.MValue {
	var protoValue *pb.MValue

	rt := reflect.TypeOf(value)
	rv := reflect.ValueOf(value)
	kind := rt.Kind()

	switch kind {
	case reflect.Ptr:
		rt = rt.Elem()
		rv = rv.Elem()

		structName := rt.Name()
		kind = rt.Kind()

		if structName == "Player" || structName == "Vehicle" || structName == "Entity" || structName == "ColShape" || structName == "Checkpoint" || structName == "VoiceChannel" || structName == "Blip" {
			// BaseObject
			protoValue = &pb.MValue{
				Value: &pb.MValue_BaseObjectValue{
					BaseObjectValue: &pb.BaseObject{
						Type: proto.Uint32(uint32(rv.FieldByName("Type").Uint())),
						Ptr:  proto.String(fmt.Sprintf("%v", rv.FieldByName("Ptr").UnsafePointer())),
					},
				},
			}
		} else if kind == reflect.Struct {
			// struct pointer
			protoValue = structToProto(rt, rv)
		} else if kind == reflect.Slice || kind == reflect.Array {
			// slice / array pointer
			protoValue = sliceToProto(rt, rv)
		} else if kind == reflect.Map {
			// map pointer
			protoValue = mapToProto(rt, rv)
		}
	case reflect.String:
		protoValue = &pb.MValue{
			Value: &pb.MValue_StringValue{
				StringValue: rv.String(),
			},
		}
	case reflect.Bool:
		protoValue = &pb.MValue{
			Value: &pb.MValue_BoolValue{
				BoolValue: rv.Bool(),
			},
		}
	case reflect.Float32, reflect.Float64:
		protoValue = &pb.MValue{
			Value: &pb.MValue_DoubleValue{
				DoubleValue: rv.Float(),
			},
		}
	case reflect.Func:
		// function
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = rv

		protoValue = &pb.MValue{
			Value: &pb.MValue_InternFunctionValue{
				InternFunctionValue: &pb.InternFunction{
					Id:           proto.Uint64(id),
					ResourceName: proto.String(CurrentResource.Name()),
				},
			},
		}
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		// mValuePtr = C.core_create_mvalue_int(C.longlong(rv.Int()))
		protoValue = &pb.MValue{
			Value: &pb.MValue_IntValue{
				IntValue: rv.Int(),
			},
		}
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		// mValuePtr = C.core_create_mvalue_uint(C.ulonglong(rv.Uint()))
		protoValue = &pb.MValue{
			Value: &pb.MValue_UintValue{
				UintValue: rv.Uint(),
			},
		}
	case reflect.Array, reflect.Slice:
		// list
		protoValue = sliceToProto(rt, rv)
	case reflect.Struct:
		// vector3, rgba, vector2
		//mValuePtr, mValueType = serializeStruct(rt, rv)
		protoValue = structToProto(rt, rv)
	case reflect.Map:
		// map
		//mValuePtr, mValueType = serializeMap(rv)
		protoValue = mapToProto(rt, rv)
	default:
		//mValueType = MValueNone
		protoValue = &pb.MValue{
			Value: &pb.MValue_NoneValue{
				NoneValue: true,
			},
		}
	}

	return protoValue
}

func serializeProtoMValue(protoValue *pb.MValue) ([]byte, error) {
	return proto.Marshal(protoValue)
}

func encode(v interface{}) (C.struct_array, error) {
	pbv := newProtoMValue(v)
	bytes, err := serializeProtoMValue(pbv)
	if err != nil {
		return C.struct_array{}, err
	}

	ptr := C.CBytes(bytes)
	return C.struct_array{
		array: ptr,
		size:  C.ulonglong(len(bytes)),
	}, nil
}

func encodeArgs(v []interface{}) (C.struct_array, error) {
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
		arr, err := encode(arg)
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
