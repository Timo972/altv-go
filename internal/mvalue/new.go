package mvalue

import (
	"fmt"
	"github.com/timo972/altv-go/internal/pb"
	"google.golang.org/protobuf/proto"
	"os"
	"reflect"
)

func New(v interface{}) (pv *pb.MValue) {
	rt := reflect.TypeOf(v)
	rv := reflect.ValueOf(v)
	kind := rt.Kind()

	switch kind {
	case reflect.Ptr:
		rt = rt.Elem()
		rv = rv.Elem()

		structName := rt.Name()
		kind = rt.Kind()

		if structName == "Player" || structName == "Vehicle" || structName == "Entity" || structName == "ColShape" || structName == "Checkpoint" || structName == "VoiceChannel" || structName == "Blip" {
			// BaseObject
			pv = &pb.MValue{
				Value: &pb.MValue_BaseObjectValue{
					BaseObjectValue: &pb.BaseObject{
						Type: proto.Uint32(uint32(rv.FieldByName("Type").Uint())),
						Ptr:  proto.String(fmt.Sprintf("%v", rv.FieldByName("Ptr").UnsafePointer())),
					},
				},
			}
		} else if kind == reflect.Struct {
			// struct pointer
			pv = structToProto(rt, rv)
		} else if kind == reflect.Slice || kind == reflect.Array {
			// slice / array pointer
			pv = sliceToProto(rt, rv)
		} else if kind == reflect.Map {
			// map pointer
			pv = mapToProto(rt, rv)
		}
	case reflect.String:
		pv = &pb.MValue{
			Value: &pb.MValue_StringValue{
				StringValue: rv.String(),
			},
		}
	case reflect.Bool:
		pv = &pb.MValue{
			Value: &pb.MValue_BoolValue{
				BoolValue: rv.Bool(),
			},
		}
	case reflect.Float32, reflect.Float64:
		pv = &pb.MValue{
			Value: &pb.MValue_DoubleValue{
				DoubleValue: rv.Float(),
			},
		}
	case reflect.Func:
		// function
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = rv

		pv = &pb.MValue{
			Value: &pb.MValue_InternFunctionValue{
				InternFunctionValue: &pb.InternFunction{
					Id:           proto.Uint64(id),
					ResourceName: proto.String(os.Getenv("resourceName")),
				},
			},
		}
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		// mValuePtr = C.core_create_mvalue_int(C.longlong(rv.Int()))
		pv = &pb.MValue{
			Value: &pb.MValue_IntValue{
				IntValue: rv.Int(),
			},
		}
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		// mValuePtr = C.core_create_mvalue_uint(C.ulonglong(rv.Uint()))
		pv = &pb.MValue{
			Value: &pb.MValue_UintValue{
				UintValue: rv.Uint(),
			},
		}
	case reflect.Array, reflect.Slice:
		// list
		pv = sliceToProto(rt, rv)
	case reflect.Struct:
		// vector3, rgba, vector2
		//mValuePtr, mValueType = serializeStruct(rt, rv)
		pv = structToProto(rt, rv)
	case reflect.Map:
		// map
		//mValuePtr, mValueType = serializeMap(rv)
		pv = mapToProto(rt, rv)
	default:
		//mValueType = MValueNone
		pv = &pb.MValue{
			Value: &pb.MValue_NoneValue{
				NoneValue: true,
			},
		}
	}

	return
}
