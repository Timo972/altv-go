package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"errors"
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

type MValue struct {
	Ptr   unsafe.Pointer
	Type  MValueType
	Value interface{}
}

type ExternFunction struct {
	Ptr unsafe.Pointer
}

func (e ExternFunction) String() string {
	return "ExternFunction{}"
}

func (e ExternFunction) Call(args ...interface{}) (interface{}, error) {
	if e.Ptr == nil {
		return nil, errors.New("invalid extern function")
	}

	cArgPtr, cArgSize := newMValueArray(args)
	defer C.free(unsafe.Pointer(cArgPtr))

	cMeta := C.call_mvalue_function(e.Ptr, cArgPtr, cArgSize)
	mVal := &MValue{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}

	var val interface{}
	ok := mVal.GetValue(&val)
	if !ok {
		return val, errors.New("mvalue conversion failed")
	}

	return val, nil
}

func CreateMValue(value interface{}) *MValue {
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

		LogInfo("created mvalue function:", id)
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

	return &MValue{Ptr: mValuePtr, Type: mValueType}
}

func (v MValue) GetValue(val interface{}) (ok bool) {
	if reflect.TypeOf(val).Kind() != reflect.Ptr {
		return false
	}

	rv := reflect.ValueOf(val).Elem()
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

		var ev reflect.Value
		if _type == PlayerObject {
			ev = reflect.ValueOf(newPlayer(entity.Ptr))
		} else if _type == VehicleObject {
			ev = reflect.ValueOf(newVehicle(entity.Ptr))
		} else if _type == ColshapeObject {
			ev = reflect.ValueOf(newColShape(entity.Ptr))
		} else if _type == CheckpointObject {
			ev = reflect.ValueOf(newCheckpoint(entity.Ptr))
		} else if _type == VoiceChannelObject {
			ev = reflect.ValueOf(newVoiceChannel(entity.Ptr))
		} else if _type == BlipObject {
			ev = reflect.ValueOf(newBlip(entity.Ptr))
		}

		if !ev.IsValid() || ev.IsZero() || ev.IsNil() {
			return false
		}

		rv.Set(ev.Elem())
	case MValueVector2:
		rv.Set(reflect.ValueOf(newVector2(C.core_get_mvalue_vector2(v.Ptr))))
	case MValueVector3:
		rv.Set(reflect.ValueOf(newVector3(C.core_get_mvalue_vector3(v.Ptr))))
	case MValueRGBA:
		rv.Set(reflect.ValueOf(newRGBA(C.core_get_mvalue_rgba(v.Ptr))))
	case MValueByteArray:
		arr := C.core_get_mvalue_byte_array(v.Ptr)
		rv.Set(reflect.ValueOf(C.GoBytes(arr.array, C.int(arr.size))))
	case MValueFunction:
		ev := reflect.ValueOf(ExternFunction{
			Ptr: v.Ptr,
		})

		rv.Set(ev)
	default:
		ok = true
	}
	return !ok
}

func (v MValue) CStruct() C.struct_data {
	return C.struct_data{mValue: v.Ptr, Type: C.uint(v.Type)}
}

//export altCallFunction
func altCallFunction(id C.ulonglong, cMValues unsafe.Pointer, cSize C.ulonglong) C.struct_data {
	exportedFunc := mValueFunctions[uint64(id)]

	args := convertMValueArray(cMValues, cSize)
	rvArgs := make([]reflect.Value, len(args))
	for i, arg := range args {
		if arg == nil {
			LogError("exported function called with nil argument")
			return C.struct_data{mValue: nil, Type: C.uint(MValueNone)}
		}
		rvArgs[i] = reflect.ValueOf(arg)
	}

	resValues := exportedFunc.Call(rvArgs)

	size := len(resValues)
	if size > 1 {
		LogWarning("exported function returned more than 1 argument, which is currently not supported (dropping overflow)")
	} else if size == 0 {
		return C.struct_data{mValue: nil, Type: C.uint(MValueNone)}
	}

	mValue := CreateMValue(resValues[0].Interface())

	return mValue.CStruct()
}
