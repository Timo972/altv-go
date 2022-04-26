package alt

// #cgo CFLAGS: -I../c-api/lib
// #cgo LDFLAGS: -L../c-api/lib -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"errors"
	"fmt"
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

	arr, err := encodeArgs(args)
	defer C.free(unsafe.Pointer(arr.array))
	if err != nil {
		return nil, err
	}

	cMeta := C.runtime_call_m_value_function(e.Ptr, arr)
	//mVal := &MValue{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}
	val, err := decodeReflect(cMeta)
	if err != nil {
		return nil, err
	}

	return val, nil
}

//export altCallFunction
func altCallFunction(id C.ulonglong, cMValueArgs C.struct_array) C.struct_array {
	exportedFunc := mValueFunctions[uint64(id)]

	var err error

	argsSize := int(cMValueArgs.size)
	mValueArgs := (*[1 << 30]C.struct_array)(cMValueArgs.array)

	funcType := exportedFunc.Type()
	argCount := funcType.NumIn()
	args := make([]reflect.Value, argCount)

	if argsSize != argCount {
		LogError("failed to call exported function: argument count mismatch")
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	for i := 0; i < argCount; i++ {
		argType := funcType.In(i)
		out := reflect.New(argType)

		bytes := C.GoBytes(mValueArgs[i].array, C.int(mValueArgs[i].size))

		d := &Decoder{
			Buffer:    bytes,
			RootType:  argType,
			RootValue: out.Elem(),
		}
		err = d.unmarshalBytes()
		if err != nil {
			LogError("failed to call exported function:", err.Error())
			return C.struct_array{array: nil, size: C.ulonglong(0)}
		}

		err = d.decode()
		if err != nil {
			LogError("failed to call exported function:", err.Error())
			return C.struct_array{array: nil, size: C.ulonglong(0)}
		}

		args[i] = d.RootValue
	}

	if len(args) != argCount {
		LogError(fmt.Sprintf("failed to call exported function: argument count mismatch (required: %v, got: %v) - dont pass nil / none values", argCount, len(args)))
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	resValues := exportedFunc.Call(args)
	size := len(resValues)

	if size == 0 {
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	var returnValue interface{}

	if size > 1 {
		// LogWarning("exported function returned more than 1 argument, which is currently not supported (dropping overflow)")
		values := make([]interface{}, size)
		for i, v := range resValues {
			values[i] = v.Interface()
		}

		returnValue = values
	} else {
		returnValue = resValues[0].Interface()
	}

	cBytes, err := encode(returnValue)
	if err != nil {
		LogError("exported function returned invalid value: %s", err.Error())
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	return cBytes
}
