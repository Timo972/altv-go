package alt

// #include "Module.h"
import "C"
import (
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
)

type MValueType = uint8

const (
	MValueNone MValueType = iota
	MValueBool
	MValueInt
	MValueUInt
	MValueDouble
	MValueString
	MValueList
	MValueDict
	MValueBaseObject
	MValueFunction
	MValueVector2
	MValueVector3
	MValueRGBA
	MValueByteArray
)

type MValue struct {
	Ptr   unsafe.Pointer
	Type  MValueType
	Value interface{}
}

func CreateMValue(value interface{}) *MValue {
	var mValue unsafe.Pointer
	var mValueType MValueType

	switch value.(type) {
	case bool:
		mValue = C.core_create_mvalue_bool(C.int(module.Bool2int(value.(bool))))
		mValueType = MValueBool
	case int, int8, int16, int32, int64:
		mValue = C.core_create_mvalue_int(C.longlong(value.(int64)))
		mValueType = MValueInt
	case uint, uint8, uint16, uint32, uint64:
		mValue = C.core_create_mvalue_uint(C.ulonglong(value.(uint64)))
		mValueType = MValueUInt
	case float32, float64:
		mValue = C.core_create_mvalue_double(C.double(value.(float64)))
		mValueType = MValueDouble
	case string:
		cstr := C.CString(value.(string))
		defer C.free(unsafe.Pointer(cstr))

		mValue = C.core_create_mvalue_string(cstr)
		mValueType = MValueString
	}

	return &MValue{Ptr: mValue, Type: mValueType, Value: nil}
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
	}

	return v.Value
}

func (v MValue) GetType() MValueType {
	return v.Type
}
