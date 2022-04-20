package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
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
				BaseObjectValue: &pb.BaseObject{
					Type: proto.Uint32(uint32(rv.FieldByName("Type").Uint())),
					Ptr:  proto.String(fmt.Sprintf("%v", rv.FieldByName("Ptr").UnsafePointer())),
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
			StringValue: proto.String(rv.String()),
		}
		mValueType = MValueString
	case reflect.Bool:
		protoValue = &pb.MValue{
			BoolValue: proto.Bool(rv.Bool()),
		}
		mValueType = MValueBool
	case reflect.Float32, reflect.Float64:
		protoValue = &pb.MValue{
			DoubleValue: proto.Float64(rv.Float()),
		}
		mValueType = MValueDouble
	case reflect.Func:
		// function
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = rv

		protoValue = &pb.MValue{
			FunctionValue: &pb.Function{
				Id: proto.Uint64(id),
				//ResourceName: alt.Resource.Name,
				ResourceName: proto.String(Resource.Name),
			},
		}
		mValueType = MValueFunction
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		// mValuePtr = C.core_create_mvalue_int(C.longlong(rv.Int()))
		mValueType = MValueInt
		protoValue = &pb.MValue{
			IntValue: proto.Int64(rv.Int()),
		}
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		// mValuePtr = C.core_create_mvalue_uint(C.ulonglong(rv.Uint()))
		mValueType = MValueUInt
		protoValue = &pb.MValue{
			UintValue: proto.Uint64(rv.Uint()),
		}
	case reflect.Array, reflect.Slice:
		//// list
		//sliceName := rt.Elem().Name()
		//
		//// byte array
		//if sliceName == "uint8" {
		//	bytes := rv.Bytes()
		//	arrayPtr := C.CBytes(bytes)
		//	defer C.free(arrayPtr)
		//
		//	mValuePtr = C.core_create_mvalue_byte_array((*C.uchar)(arrayPtr), C.ulonglong(len(bytes)))
		//	mValueType = MValueByteArray
		//} else {
		//	// every other types
		//	mValuePtr, mValueType = serializeSlice(rv)
		//}
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
			NoneValue: proto.Bool(true),
		}
		mValueType = MValueNone
	}

	return protoValue, mValueType
}

func serializeProtoMValue(protoValue *pb.MValue) ([]byte, error) {

	return proto.Marshal(protoValue)
}

/*func createProtoMValue(data []byte, mValueType MValueType) *MValue {
	arrayPtr := C.CBytes(data)
	defer C.free(arrayPtr)
	mValuePtr := C.core_create_mvalue((*C.uchar)(arrayPtr), C.ulonglong(len(data)))

	return &MValue{
		Ptr:  mValuePtr,
		Type: mValueType,
	}
}*/
