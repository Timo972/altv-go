package alt

import "C"
import (
	"reflect"

	"github.com/timo972/altv-go-pkg/pb"
	"google.golang.org/protobuf/proto"
)

type ProtoValue struct {
}

func sliceToProto(rt reflect.Type, rv reflect.Value) pb.MValue {
	return pb.MValue{}
}

func structToProto(rt reflect.Type, rv reflect.Value) pb.MValue {
	return pb.MValue{}
}

func mapToProto(rt reflect.Type, rv reflect.Value) pb.MValue {
	return pb.MValue{}
}

func createProtoMValue(value interface{}) (*pb.MValue, error) {
	//var mValuePtr unsafe.Pointer
	//var mValueType MValueType
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
			//ptr := rv.FieldByName("Ptr").UnsafePointer()
			//t := rv.FieldByName("Type").Uint()
			//
			//mValuePtr = C.core_create_mvalue_base_object(C.uchar(t), ptr)
			//mValueType = MValueBaseObject
			protoValue = &pb.MValue{
				BaseObjectValue: &pb.BaseObject{
					Type: uint32(rv.FieldByName("Type").Uint()),
					Ptr:  "",
				},
			}
		} else if kind == reflect.Struct {
			// struct pointer
			//mValuePtr, mValueType = serializeStruct(rt, rv)
			protoValue = structToProto(rt, rv)
		} else if kind == reflect.Slice || kind == reflect.Array {
			// slice / array pointer
			//mValuePtr, mValueType = serializeSlice(rv)
			protoValue = sliceToProto(rt, rv)
		} else if kind == reflect.Map {
			protoValue = mapToProto(rt, rv)
			//mValuePtr, mValueType = serializeMap(rv)
		}
	case reflect.String:
		protoValue = &pb.MValue{
			StringValue: proto.String(rv.String()),
		}
	case reflect.Bool:
		protoValue = &pb.MValue{
			BoolValue: proto.Bool(rv.Bool()),
		}
	case reflect.Float32, reflect.Float64:
		protoValue = &pb.MValue{
			DoubleValue: proto.Float64(rv.Float()),
		}
	case reflect.Func:
		// function
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = rv

		protoValue = &pb.MValue{
			FunctionValue: &pb.Function{
				Id:           id,
				ResourceName: Resource.Name,
			},
		}
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		// mValuePtr = C.core_create_mvalue_int(C.longlong(rv.Int()))
		// mValueType = MValueInt

		protoValue = &pb.MValue{
			IntValue: proto.Int64(rv.Int()),
		}
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		// mValuePtr = C.core_create_mvalue_uint(C.ulonglong(rv.Uint()))
		// mValueType = MValueUInt
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
		sliceToProto(rt, rv)
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
			NoneValue: proto.Bool(true),
		}
	}

	out, err := proto.Marshal(protoValue)
	if err != nil {
		return nil, err
	}

	arrayPtr := C.CBytes(out)
	defer C.free(arrayPtr)

	C.core_create_mvalue((*C.uchar)(arrayPtr), C.ulonglong(len(out)))

	return protoValue, nil
}
