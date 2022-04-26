package alt

// #cgo CFLAGS: -I../c-api/lib
// #cgo LDFLAGS: -L../c-api/lib -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"fmt"
	"reflect"

	"github.com/timo972/altv-go-pkg/pb"
	"google.golang.org/protobuf/proto"
)

func newProtoMValue(value interface{}) (*pb.MValue, MValueType) {
	var mValueType MValueType
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
			mValueType = MValueBaseObject
		} else if kind == reflect.Struct {
			// struct pointer
			protoValue, mValueType = structToProto(rt, rv)
		} else if kind == reflect.Slice || kind == reflect.Array {
			// slice / array pointer
			protoValue, mValueType = sliceToProto(rt, rv)
		} else if kind == reflect.Map {
			// map pointer
			protoValue, mValueType = mapToProto(rt, rv)
		}
	case reflect.String:
		protoValue = &pb.MValue{
			Value: &pb.MValue_StringValue{
				StringValue: rv.String(),
			},
		}
		mValueType = MValueString
	case reflect.Bool:
		protoValue = &pb.MValue{
			Value: &pb.MValue_BoolValue{
				BoolValue: rv.Bool(),
			},
		}
		mValueType = MValueBool
	case reflect.Float32, reflect.Float64:
		protoValue = &pb.MValue{
			Value: &pb.MValue_DoubleValue{
				DoubleValue: rv.Float(),
			},
		}
		mValueType = MValueDouble
	case reflect.Func:
		// function
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = rv

		protoValue = &pb.MValue{
			Value: &pb.MValue_InternFunctionValue{
				InternFunctionValue: &pb.InternFunction{
					Id: proto.Uint64(id),
					//ResourceName: alt.Resource.Name,
					ResourceName: proto.String(Resource.Name),
				},
			},
		}
		mValueType = MValueFunction
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		// mValuePtr = C.core_create_mvalue_int(C.longlong(rv.Int()))
		mValueType = MValueInt
		protoValue = &pb.MValue{
			Value: &pb.MValue_IntValue{
				IntValue: rv.Int(),
			},
		}
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		// mValuePtr = C.core_create_mvalue_uint(C.ulonglong(rv.Uint()))
		mValueType = MValueUInt
		protoValue = &pb.MValue{
			Value: &pb.MValue_UintValue{
				UintValue: rv.Uint(),
			},
		}
	case reflect.Array, reflect.Slice:
		// list
		protoValue, mValueType = sliceToProto(rt, rv)
	case reflect.Struct:
		// vector3, rgba, vector2
		//mValuePtr, mValueType = serializeStruct(rt, rv)
		protoValue, mValueType = structToProto(rt, rv)
	case reflect.Map:
		// map
		//mValuePtr, mValueType = serializeMap(rv)
		protoValue, mValueType = mapToProto(rt, rv)
	default:
		//mValueType = MValueNone
		protoValue = &pb.MValue{
			Value: &pb.MValue_NoneValue{
				NoneValue: true,
			},
		}
		mValueType = MValueNone
	}

	return protoValue, mValueType
}

func serializeProtoMValue(protoValue *pb.MValue) ([]byte, error) {
	return proto.Marshal(protoValue)
}

func encode(v interface{}) (C.struct_array, error) {
	pbv, _ := newProtoMValue(v)
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
