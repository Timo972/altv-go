package alt

// #cgo CFLAGS: -I../c-api/build/Release
// #cgo LDFLAGS: -L../c-api/build/Release -lcapi
// #include <stdlib.h>
// #include "../c-api/capi.h"
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

	/*cArgPtr, cArgSize := newMValueArray(args)
	defer C.free(unsafe.Pointer(cArgPtr))

	cMeta := C.runtime_call_m_value_function(e.Ptr, cArgPtr, cArgSize)
	mVal := &MValue{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}

	var val interface{}
	ok := mVal.Value(&val)
	if !ok {
		return val, errors.New("mvalue conversion failed")
	}

	return val, nil*/
	return nil, nil
}

//export altCallFunction
func altCallFunction(id C.ulonglong, cByteArray C.struct_array) C.struct_array {
	exportedFunc := mValueFunctions[uint64(id)]

	rvArgs := make([]reflect.Value, 0)
	/*for i, arg := range args {
		if arg == nil {
			LogError("exported function called with nil argument")
			return C.struct_array{array: nil, size: C.ulonglong(0)}
		}
		rvArgs[i] = reflect.ValueOf(arg)
	}*/

	resValues := exportedFunc.Call(rvArgs)

	size := len(resValues)
	if size > 1 {
		LogWarning("exported function returned more than 1 argument, which is currently not supported (dropping overflow)")
	} else if size == 0 {
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	cBytes, err := encode(resValues[0].Interface())
	if err != nil {
		LogError("exported function returned invalid value: %s", err.Error())
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	return cBytes
}
