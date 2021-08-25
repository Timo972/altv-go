package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"encoding/json"
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
)

type MValueType = uint8

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

type MValue struct {
	Ptr   unsafe.Pointer
	Type  MValueType
	Value interface{}
}

func CreateMValue(value interface{}) *MValue {
	var mValuePtr unsafe.Pointer
	var mValueType MValueType

	switch t := value.(type) {
	case bool:
		mValuePtr = C.core_create_mvalue_bool(C.int(module.Bool2int(value.(bool))))
		mValueType = MValueBool
	case int:
	case int8:
	case int16:
	case int32:
	case int64:
		mValuePtr = C.core_create_mvalue_int(C.longlong(int64(t)))
		mValueType = MValueInt
	case uint:
	case uint8:
	case uint16:
	case uint32:
	case uint64:
		mValuePtr = C.core_create_mvalue_uint(C.ulonglong(value.(uint64)))
		mValueType = MValueUInt
	case float32:
	case float64:
		mValuePtr = C.core_create_mvalue_double(C.double(value.(float64)))
		mValueType = MValueDouble
	case string:
		cstr := C.CString(value.(string))
		defer C.free(unsafe.Pointer(cstr))

		mValuePtr = C.core_create_mvalue_string(cstr)
		mValueType = MValueString
	case []interface{}:
	case []bool:
	case []int:
	case []int8:
	case []int16:
	case []int32:
	case []int64:
	case []string:
	case []uint:
	case []uint8:
	case []uint16:
	case []uint32:
	case []uint64:
	case []float32:
	case []float64:
		js, _ := json.Marshal(value)
		cJson := C.CString(string(js))
		defer C.free(unsafe.Pointer(cJson))
		size := len(value.([]interface{}))

		mValuePtr = C.core_create_mvalue_list(cJson, C.ulonglong(size))
		mValueType = MValueList
	default:
		mValuePtr = nil
		mValueType = MValueNone
	}

	return &MValue{Ptr: mValuePtr, Type: mValueType, Value: nil}
}

func (v MValue) GetValue() interface{} {
	switch v.Type {
	case MValueBool:
		v.Value = int(C.core_get_mvalue_bool(v.Ptr)) != 0
	case MValueInt:
		v.Value = int64(C.core_get_mvalue_int(v.Ptr))
	case MValueUInt:
		v.Value = uint64(C.core_get_mvalue_uint(v.Ptr))
	case MValueDouble:
		v.Value = float64(C.core_get_mvalue_double(v.Ptr))
	case MValueString:
		v.Value = C.GoString(C.core_get_mvalue_string(v.Ptr))
	default:
		v.Value = nil
	}

	return v.Value
}

func (v MValue) GetType() MValueType {
	return v.Type
}
