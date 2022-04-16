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
	Ptr  unsafe.Pointer
	Type MValueType
	Val  reflect.Value
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
	ok := mVal.Value(&val)
	if !ok {
		return val, errors.New("mvalue conversion failed")
	}

	return val, nil
}

func newStructMValue(rt reflect.Type, rv reflect.Value) (unsafe.Pointer, MValueType) {
	var mValuePtr unsafe.Pointer
	var mValueType MValueType

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
	} else {
		// user struct

		fieldCount := rv.NumField()
		allCount := fieldCount + rv.NumMethod()

		keysPtr := C.malloc(C.size_t(allCount) * C.size_t(unsafe.Sizeof(uintptr(0))))
		cKeys := (*[1 << 30]*C.char)(keysPtr)

		mValuesPtr := C.malloc(C.size_t(C.sizeof_MetaData * allCount))
		cMValues := (*[1 << 30]unsafe.Pointer)(mValuesPtr)

		// export data
		for i := 0; i < fieldCount; i++ {
			field := rv.Field(i)
			fieldType := rt.Field(i)

			fieldName := getFieldName(fieldType)
			cKeys[i] = C.CString(fieldName)
			mValue := CreateMValue(field.Interface())
			cMValues[i] = mValue.Ptr //mValue.CStruct()
		}

		// export methods
		for i := fieldCount; i < allCount; i++ {
			method := rt.Method(i)
			// this enabled means you can not export methods in camelCase - only PascalCase
			// if !method.IsExported() {
			// 	continue
			// }
			methodName := method.Type.Name()
			cKeys[i] = C.CString(methodName)
			mValue := CreateMValue(method.Func.Interface())
			cMValues[i] = mValue.Ptr //mValue.CStruct()
		}

		mValuePtr = C.core_create_mvalue_dict((**C.char)(keysPtr), (*unsafe.Pointer)(mValuesPtr), C.ulonglong(allCount))
		mValueType = MValueDict
	}

	return mValuePtr, mValueType
}

func newSliceMValue(rv reflect.Value) (unsafe.Pointer, MValueType) {
	size := rv.Len()
	mValuesPtr := C.malloc(C.size_t(C.sizeof_MetaData) * C.size_t(size))
	cMValues := (*[1 << 30]unsafe.Pointer)(mValuesPtr)

	for i := 0; i < size; i++ {
		item := rv.Index(i)
		mValue := CreateMValue(item.Interface())
		cMValues[i] = mValue.Ptr //mValue.CStruct()
	}

	mValuePtr := C.core_create_mvalue_list((*unsafe.Pointer)(mValuesPtr), C.ulonglong(size))
	return mValuePtr, MValueList
}

func newMapMValue(rv reflect.Value) (unsafe.Pointer, MValueType) {
	keys := rv.MapKeys()
	size := len(keys)

	keysPtr := C.malloc(C.size_t(size) * C.size_t(unsafe.Sizeof(uintptr(0))))
	cKeys := (*[1 << 30]*C.char)(keysPtr)

	mValuesPtr := C.malloc(C.size_t(C.sizeof_MetaData * size))
	cMValues := (*[1 << 30]unsafe.Pointer)(mValuesPtr)

	for i, key := range keys {
		cKeys[i] = C.CString(key.String())
		mValue := CreateMValue(rv.MapIndex(key).Interface())
		cMValues[i] = mValue.Ptr
	}

	mValuePtr := C.core_create_mvalue_dict((**C.char)(keysPtr), (*unsafe.Pointer)(mValuesPtr), C.ulonglong(size))
	return mValuePtr, MValueDict
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
				mValue := &MValue{Ptr: cValue.Ptr, Type: uint8(cValue.Type), Val: field}
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

func CreateMValue(value interface{}) *MValue {
	var mValuePtr unsafe.Pointer
	var mValueType MValueType

	rt := reflect.TypeOf(value)
	rv := reflect.ValueOf(value)
	kind := rt.Kind()

	switch kind {
	case reflect.Ptr:
		rt = rt.Elem()
		rv = rv.Elem()

		structName := rt.Name()

		if structName == "Player" || structName == "Vehicle" || structName == "Entity" || structName == "ColShape" || structName == "Checkpoint" || structName == "VoiceChannel" || structName == "Blip" {
			// BaseObject
			ptr := rv.FieldByName("Ptr").UnsafePointer()
			t := rv.FieldByName("Type").Uint()

			mValuePtr = C.core_create_mvalue_base_object(C.uchar(t), ptr)
			mValueType = MValueBaseObject
		} else if rt.Kind() == reflect.Struct {
			// struct pointer
			mValuePtr, mValueType = newStructMValue(rt, rv)
		} else if rt.Kind() == reflect.Slice || rt.Kind() == reflect.Array {
			// slice / array pointer
			mValuePtr, mValueType = newSliceMValue(rv)
		} else if rt.Kind() == reflect.Map {
			mValuePtr, mValueType = newMapMValue(rv)
		}
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
		} else {
			// every other types
			mValuePtr, mValueType = newSliceMValue(rv)
		}
	case reflect.Struct:
		// vector3, rgba, vector2
		mValuePtr, mValueType = newStructMValue(rt, rv)
	case reflect.Map:
		// map
		mValuePtr, mValueType = newMapMValue(rv)
	default:
		mValueType = MValueNone
	}

	return &MValue{Ptr: mValuePtr, Type: mValueType, Val: rv}
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

		v.Val = ev //ev.Elem()
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
		if v.Val.IsValid() {
			v.Val = parseMValueList(&v, v.Val.Type())
		} else {
			LogError("[MValue] can not parse nested maps")
		}
		// C.free(arr.array)
	case MValueDict:
		if v.Val.IsValid() {
			parseMValueDict(&v, v.Val.Type(), v.Val)
		} else {
			LogError("[MValue] can not parse nested maps")
		}
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

	mValue := CreateMValue(resValues[0].Interface())

	return mValue.CStruct()
}
