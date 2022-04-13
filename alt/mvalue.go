package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"reflect"
	"unsafe"

	"github.com/timo972/altv-go-pkg/internal/module"
)

type MValueType = uint8

// type MValueFunc = func(args ...interface{}) interface{}

const (
	MValueNone MValueType = iota
	MValueNil
	MValueBool
	MValueInt
	MValueUInt
	MValueDouble
	MValueString
	MValueList
	MValueDict
	MValueBaseObject
	MValueFunction
	MValueVector3
	MValueRGBA
	MValueByteArray
	MValueVector2
)

var (
	mValueFuncCount = uint64(0)
	mValueFunctions = make(map[uint64]reflect.Value)
)

type MValue[ValueType any] struct {
	Ptr   unsafe.Pointer
	Type  MValueType
	Value ValueType
}

func CreateMValue[V any](value V) *MValue[V] {
	var mValuePtr unsafe.Pointer
	var mValueType MValueType

	rt := reflect.TypeOf(value)
	rv := reflect.ValueOf(value)
	kind := rt.Kind()

	switch kind {
	case reflect.Ptr:
		structName := rt.Elem().Name()
		if structName != "Player" && structName != "Vehicle" && structName != "Entity" && structName != "ColShape" && structName != "Checkpoint" && structName != "VoiceChannel" && structName != "Blip" {
			mValueType = MValueNil

			break
		}

		// BaseObject
		ptr := rv.FieldByName("Ptr").UnsafePointer()
		t := rv.FieldByName("Type").Uint()

		mValuePtr = C.core_create_mvalue_base_object(C.uchar(t), ptr)
		mValueType = MValueBaseObject
	case reflect.String:
		// string
		cstr := C.CString(rv.String())
		defer C.free(unsafe.Pointer(cstr))

		mValuePtr = C.core_create_mvalue_string(cstr)
		mValueType = MValueString
	case reflect.Bool:
		// bool
		mValuePtr = C.core_create_mvalue_bool(C.int(module.Bool2int(rv.Bool())))
		mValueType = MValueBool
	case reflect.Float32, reflect.Float64:
		// double
		mValuePtr = C.core_create_mvalue_double(C.double(rv.Float()))
		mValueType = MValueDouble
	case reflect.Func:
		// function
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = rv

		cResource := C.CString(Resource.Name)
		defer C.free(unsafe.Pointer(cResource))

		mValuePtr = C.create_mvalue_function(cResource, C.ulonglong(id))
		mValueType = MValueFunction
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		mValuePtr = C.core_create_mvalue_int(C.longlong(rv.Int()))
		mValueType = MValueInt
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		mValuePtr = C.core_create_mvalue_uint(C.ulonglong(rv.Uint()))
		mValueType = MValueUInt
	case reflect.Array, reflect.Slice:
		// list
		sliceName := rt.Elem().Name()

		// byte array
		if sliceName == "uint8" {
			bytes := rv.Bytes()
			arrayPtr := C.CBytes(bytes)
			defer C.free(arrayPtr)

			mValuePtr = C.core_create_mvalue_byte_array((*C.uchar)(arrayPtr), C.ulonglong(len(bytes)))
			mValueType = MValueByteArray
		}
	case reflect.Struct:
		// vector3, rgba, vector2
		structName := rt.Name()

		if structName == "RGBA" {
			r := rv.FieldByName("R").Uint()
			g := rv.FieldByName("G").Uint()
			b := rv.FieldByName("B").Uint()
			a := rv.FieldByName("A").Uint()

			mValuePtr = C.core_create_mvalue_rgba(C.uchar(r), C.uchar(g), C.uchar(b), C.uchar(a))
			mValueType = MValueRGBA
		} else if structName == "Vector2" {
			x := rv.FieldByName("X").Float()
			y := rv.FieldByName("Y").Float()

			mValuePtr = C.core_create_mvalue_vector2(C.float(x), C.float(y))
			mValueType = MValueVector2
		} else if structName == "Vector3" {
			x := rv.FieldByName("X").Float()
			y := rv.FieldByName("Y").Float()
			z := rv.FieldByName("Z").Float()

			mValuePtr = C.core_create_mvalue_vector3(C.float(x), C.float(y), C.float(z))
			mValueType = MValueVector3
		}
	default:
		mValueType = MValueNone
	}

	/*switch value.(type) {
	case bool:
		mValuePtr = C.core_create_mvalue_bool(C.int(module.Bool2int(value.(bool))))
		mValueType = MValueBool
	case int, int8, int16, int32, int64:
		if val, ok := value.(int); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int8); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int16); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int32); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int64); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		}
		mValueType = MValueInt
	case uint, uint8, uint16, uint32, uint64:
		if val, ok := value.(uint); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint8); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint16); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint32); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint64); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		}
		mValueType = MValueUInt
	case float32, float64:
		if val, ok := value.(float32); ok {
			mValuePtr = C.core_create_mvalue_double(C.double(val))
		} else if val, ok := value.(float64); ok {
			mValuePtr = C.core_create_mvalue_double(C.double(val))
		}
		mValueType = MValueDouble
	case string:
		cstr := C.CString(value.(string))
		defer C.free(unsafe.Pointer(cstr))

		mValuePtr = C.core_create_mvalue_string(cstr)
		mValueType = MValueString
	case []interface{}, []bool, []string, []int, []int8, []int16, []int32, []int64, []uint, []uint16, []uint32, []uint64, []float32, []float64:
		js, _ := json.Marshal(value)
		cJson := C.CString(string(js))
		defer C.free(unsafe.Pointer(cJson))
		size := len(value.([]interface{}))

		mValuePtr = C.core_create_mvalue_list(cJson, C.ulonglong(size))
		mValueType = MValueList
	case []byte:
		data := value.([]byte)
		size := len(data)
		arrayPtr := C.CBytes(data)
		defer C.free(arrayPtr)

		mValuePtr = C.core_create_mvalue_byte_array((*C.uchar)(arrayPtr), C.ulonglong(size))
		mValueType = MValueByteArray
	case RGBA:
		color := value.(RGBA)

		mValuePtr = C.core_create_mvalue_rgba(C.uchar(color.R), C.uchar(color.G), C.uchar(color.B), C.uchar(color.A))
		mValueType = MValueRGBA
	case Vector2:
		v2 := value.(Vector2)

		mValuePtr = C.core_create_mvalue_vector2(C.float(v2.X), C.float(v2.Y))
		mValueType = MValueVector3
	case Vector3:
		v3 := value.(Vector3)

		mValuePtr = C.core_create_mvalue_vector3(C.float(v3.X), C.float(v3.Y), C.float(v3.Z))
		mValueType = MValueVector3
	case *Player, *Vehicle, *ColShape, *Checkpoint, *VoiceChannel, *Blip, *Entity:
		var ptr unsafe.Pointer
		var _type BaseObjectType

		if player, ok := value.(*Player); ok {
			ptr = player.Ptr
			_type = player.Type
		}

		if vehicle, ok := value.(*Vehicle); ok {
			ptr = vehicle.Ptr
			_type = vehicle.Type
		}

		if colShape, ok := value.(*ColShape); ok {
			ptr = colShape.Ptr
			_type = colShape.Type
		}

		if checkpoint, ok := value.(*Checkpoint); ok {
			ptr = checkpoint.Ptr
			_type = checkpoint.Type
		}

		if voiceChannel, ok := value.(*VoiceChannel); ok {
			ptr = voiceChannel.Ptr
			_type = voiceChannel.Type
		}

		if blip, ok := value.(*Blip); ok {
			ptr = blip.Ptr
			_type = blip.Type
		}

		if entity, ok := value.(*Entity); ok {
			ptr = entity.Ptr
			_type = entity.Type
		}

		if ptr == nil {
			mValuePtr = nil
			mValueType = MValueNone
			break
		}

		mValuePtr = C.core_create_mvalue_base_object(C.uchar(_type), ptr)
		mValueType = MValueBaseObject
	case MValueFunc:
		mValueFunc := value.(MValueFunc)
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = mValueFunc

		cResource := C.CString(Resource.Name)
		defer C.free(unsafe.Pointer(cResource))

		mValuePtr = C.create_mvalue_function(cResource, C.ulonglong(id))
		mValueType = MValueFunction
	default:
		mValuePtr = nil
		mValueType = MValueNone
	}*/

	return &MValue[V]{Ptr: mValuePtr, Type: mValueType}
}

func (v MValue[V]) GetValue() (val V, ok bool) {
	rv := reflect.ValueOf(val)
	switch v.Type {
	case MValueBool:
		rv.SetBool(int(C.core_get_mvalue_bool(v.Ptr)) != 0)
	case MValueInt:
		rv.SetInt(int64(C.core_get_mvalue_int(v.Ptr)))
	case MValueUInt:
		rv.SetUint(uint64(C.core_get_mvalue_uint(v.Ptr)))
	case MValueDouble:
		rv.SetFloat(float64(C.core_get_mvalue_double(v.Ptr)))
	case MValueString:
		rv.SetString(C.GoString(C.core_get_mvalue_string(v.Ptr)))
	case MValueBaseObject:
		entity := C.core_get_mvalue_base_object(v.Ptr)
		_type := uint8(entity.Type)
		if _type == PlayerObject {
			rv.Set(reflect.ValueOf(newPlayer(entity.Ptr)))
		} else if _type == VehicleObject {
			rv.Set(reflect.ValueOf(newVehicle(entity.Ptr)))
		} else if _type == ColshapeObject {
			rv.Set(reflect.ValueOf(newColShape(entity.Ptr)))
		} else if _type == CheckpointObject {
			rv.Set(reflect.ValueOf(newCheckpoint(entity.Ptr)))
		} else if _type == VoiceChannelObject {
			rv.Set(reflect.ValueOf(newVoiceChannel(entity.Ptr)))
		} else if _type == BlipObject {
			rv.Set(reflect.ValueOf(newBlip(entity.Ptr)))
		}
	case MValueVector2:
		rv.Set(reflect.ValueOf(newVector2(C.core_get_mvalue_vector2(v.Ptr))))
	case MValueVector3:
		rv.Set(reflect.ValueOf(newVector3(C.core_get_mvalue_vector3(v.Ptr))))
	case MValueRGBA:
		rv.Set(reflect.ValueOf(newRGBA(C.core_get_mvalue_rgba(v.Ptr))))
	case MValueByteArray:
		arr := C.core_get_mvalue_byte_array(v.Ptr)
		rv.Set(reflect.ValueOf(C.GoBytes(arr.array, C.int(arr.size))))
	//case MValueFunction:
	//	v.Value = V(func(args ...interface{}) (interface{}, bool) {
	//		cArgPtr, cArgSize := newMValueArray(args)
	//		defer C.free(unsafe.Pointer(cArgPtr))
	//
	//		cMeta := C.call_mvalue_function(v.Ptr, cArgPtr, cArgSize)
	//		mVal := &MValue{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}
	//
	//		return mVal.GetValue()
	//	})
	default:
		ok = true
	}

	if !ok {
		v.Value, ok = rv.Interface().(V)
	}

	return v.Value, !ok
}

/*func (v MValue[V, B]) GetFunction() (V, bool) {
	if v.Type != MValueFunction {
		return V{}, false
	}

	return V(func(args ...interface{}) (B, bool) {
		cArgPtr, cArgSize := newMValueArray(args)
		defer C.free(unsafe.Pointer(cArgPtr))

		cMeta := C.call_mvalue_function(v.Ptr, cArgPtr, cArgSize)
		mVal := &MValue[B]{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}
		return mVal.GetValue()
	}), true
}*/

func (v MValue[V]) GetType() MValueType {
	return v.Type
}

//export altCallFunction
func altCallFunction(id C.ulonglong, cMValues unsafe.Pointer, cSize C.ulonglong) C.struct_data {
	listener := mValueFunctions[uint64(id)]

	//if listener == nil {
	//	mVal := CreateMValue(nil)
	//	return C.struct_data{mValue: mVal.Ptr, Type: C.uint(mVal.Type)}
	//}

	args := convertMValueArray(cMValues, cSize)
	rvArgs := make([]reflect.Value, len(args))
	for i, arg := range args {
		rvArgs[i] = reflect.ValueOf(arg)
	}

	resValues := listener.Call(rvArgs)
	size := len(resValues)
	if size > 1 {
		LogWarning("exported function returned more than 1 argument, which is currently not supported (dropping overflow)")
	} else if size == 0 {
		return C.struct_data{mValue: nil, Type: C.uint(MValueNone)}
	}

	mValue := CreateMValue[interface{}](resValues[0].Interface())
	//resInterfaces := make([]interface{}, len(resValues))
	//for i, val := range resValues {
	//	resInterfaces[i] = val.Interface()
	//}
	//
	//newMValueArray(resInterfaces)

	return C.struct_data{mValue: mValue.Ptr, Type: C.uint(mValue.Type)}
}
