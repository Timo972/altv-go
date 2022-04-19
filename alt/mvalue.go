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
	Ptr  unsafe.Pointer
	Type MValueType
	Val  reflect.Value
	Typ  reflect.Type
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

	cMeta := C.core_call_mvalue_function(e.Ptr, cArgPtr, cArgSize)
	mVal := &MValue{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}

	var val interface{}
	ok := mVal.Value(&val)
	if !ok {
		return val, errors.New("mvalue conversion failed")
	}

	return val, nil
}

func createMValue(value interface{}) (*MValue, error) {
	protoValue, mValueType := newProtoMValue(value)

	out, err := serializeProtoMValue(protoValue)
	if err != nil {
		return nil, err
	}

	return createProtoMValue(out, mValueType), nil
}

func parseMValueList(v *MValue, rt reflect.Type) reflect.Value {
	arr := C.core_get_mvalue_list(v.Ptr)

	size := int(arr.size)

	args := reflect.MakeSlice(rt, size, size)

	cValues := (*[1 << 30]C.struct_metaData)(arr.array)[:size:size]

	for i := 0; i < size; i++ {
		cValue := cValues[i]
		mValue := &MValue{Ptr: cValue.Ptr, Type: uint8(cValue.Type)}
		args.Index(i).Set(mValue.ReflectValue())
		// C.free(cValue.Ptr)
	}

	// C.free(arr.array)
	return args
}

func parseMValueDict(v *MValue, rt reflect.Type, rv reflect.Value) {
	if rt.Kind() != reflect.Struct && rt.Kind() != reflect.Map {
		return
	}

	cDict := C.core_get_mvalue_dict(v.Ptr)
	size := int(cDict.size)
	keys := newStringArray(cDict.keys, size)

	valuesPtr := unsafe.Pointer(cDict.values)
	cValues := (*[1 << 30]C.struct_metaData)(valuesPtr)[:size:size]

	if rt.Kind() == reflect.Struct {
		for i := 0; i < rv.NumField(); i++ {
			fieldKey := getFieldName(rt.Field(i))

			for j, key := range keys {
				if key != fieldKey {
					continue
				}

				field := rv.Field(i)

				cValue := cValues[j]
				mValue := &MValue{Ptr: cValue.Ptr, Type: uint8(cValue.Type)}
				refVal := mValue.ReflectValue()

				if !refVal.IsValid() {
					break
				}

				if refVal.Type().Kind() != field.Kind() {
					LogWarning("[MValue] Missmatch! Field:", fieldKey, "Index:", i, "Type:", field.Type(), "Value Type:", refVal.Type(), "Value:", refVal.Interface(), "Index:", j)
					break
				}

				field.Set(refVal)

				break
				//C.free(cValue.Ptr)
			}
		}
	} else if rt.Kind() == reflect.Map {
		et := rt.Elem()
		for i, key := range keys {
			kv := reflect.ValueOf(key)

			cValue := cValues[i]
			mValue := &MValue{Ptr: cValue.Ptr, Type: uint8(cValue.Type)}
			refVal := mValue.ReflectValue()

			if !refVal.IsValid() {
				continue
			}

			if refVal.Type().Kind() != et.Kind() {
				LogWarning("[MValue] Missmatch! Field:", key, "Type:", et, "Value Type:", refVal.Type(), "Value:", refVal.Interface())
				continue
			}

			rv.SetMapIndex(kv, refVal)
		}
	}
}

func (v MValue) ReflectValue() reflect.Value {
	if v.Val.IsValid() && !v.Val.IsZero() {
		return v.Val
	}

	switch v.Type {
	case MValueBool:
		v.Val = reflect.ValueOf(int(C.core_get_mvalue_bool(v.Ptr)) != 0)
	case MValueInt:
		v.Val = reflect.ValueOf(int64(C.core_get_mvalue_int(v.Ptr)))
	case MValueUInt:
		v.Val = reflect.ValueOf(uint64(C.core_get_mvalue_uint(v.Ptr)))
	case MValueDouble:
		v.Val = reflect.ValueOf(float64(C.core_get_mvalue_double(v.Ptr)))
	case MValueString:
		v.Val = reflect.ValueOf(C.GoString(C.core_get_mvalue_string(v.Ptr)))
	case MValueBaseObject:
		entity := C.core_get_mvalue_base_object(v.Ptr)
		_type := uint8(entity.Type)

		if _type == PlayerObject {
			v.Val = reflect.ValueOf(newPlayer(entity.Ptr))
		} else if _type == VehicleObject {
			v.Val = reflect.ValueOf(newVehicle(entity.Ptr))
		} else if _type == ColshapeObject {
			v.Val = reflect.ValueOf(newColShape(entity.Ptr))
		} else if _type == CheckpointObject {
			v.Val = reflect.ValueOf(newCheckpoint(entity.Ptr))
		} else if _type == VoiceChannelObject {
			v.Val = reflect.ValueOf(newVoiceChannel(entity.Ptr))
		} else if _type == BlipObject {
			v.Val = reflect.ValueOf(newBlip(entity.Ptr))
		}
	case MValueVector2:
		v.Val = reflect.ValueOf(newVector2(C.core_get_mvalue_vector2(v.Ptr)))
	case MValueVector3:
		v.Val = reflect.ValueOf(newVector3(C.core_get_mvalue_vector3(v.Ptr)))
	case MValueRGBA:
		v.Val = reflect.ValueOf(newRGBA(C.core_get_mvalue_rgba(v.Ptr)))
	case MValueByteArray:
		arr := C.core_get_mvalue_byte_array(v.Ptr)
		v.Val = reflect.ValueOf(C.GoBytes(arr.array, C.int(arr.size)))
	case MValueFunction:
		v.Val = reflect.ValueOf(ExternFunction{
			Ptr: v.Ptr,
		})
	case MValueList:
		// if rt != nil {
		// 	v.Val = parseMValueList(&v, rt)
		// } else {
		// 	LogError("[MValue] can not parse nested maps")
		// }
		// C.free(arr.array)
	case MValueDict:
		// if rt != nil {
		// 	parseMValueDict(&v, rt, v.Val)
		// } else {
		// 	LogError("[MValue] can not parse nested maps")
		// }
	default:
	}

	return v.Val
}

func (v MValue) Value(val interface{}) (ok bool) {
	rt := reflect.TypeOf(val)
	if rt.Kind() != reflect.Ptr {
		return false
	}

	rt = rt.Elem()
	rv := reflect.ValueOf(val).Elem()
	if v.Val.IsValid() && !v.Val.IsNil() && !v.Val.IsZero() {
		rv.Set(v.Val)
		return true
	}

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

		rv.Set(ev)
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
	case MValueList:
		if rt.Kind() != reflect.Slice && rt.Kind() != reflect.Array {
			return false
		}

		args := parseMValueList(&v, rt)

		rv.Set(args)
	case MValueDict:
		if rt.Kind() != reflect.Struct && rt.Kind() != reflect.Map {
			return false
		}

		parseMValueDict(&v, rt, rv)
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

	mValue, _ := createMValue(resValues[0].Interface())

	return mValue.CStruct()
}
