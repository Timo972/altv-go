package alt

/*
#cgo windows CFLAGS: -I../../c-api/lib
#cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi

#cgo linux CFLAGS: -I../../c-api/lib
#cgo linux LDFLAGS: -g -L../../c-api/lib/linux -lcapi  -ldl

#ifndef GOLANG_APP
#define GOLANG_APP

#include <stdlib.h>
#include "capi.h"

#endif
*/
import "C"
import (
	"errors"
	"fmt"
	"reflect"
	"unsafe"
)

var (
	mValueFuncCount = uint64(0)
	mValueFunctions = make(map[uint64]reflect.Value)
)

type ExternFunction struct {
	ptr unsafe.Pointer
}

func (e ExternFunction) String() string {
	return "ExternFunction{}"
}

func (e ExternFunction) Call(args ...interface{}) (interface{}, error) {
	if e.ptr == nil {
		return nil, errors.New("invalid extern function")
	}

	arr, err := encodeArgs(args)
	defer C.free(unsafe.Pointer(arr.array))
	if err != nil {
		return nil, err
	}

	cMeta := C.runtime_call_m_value_function(e.ptr, arr)
	//mVal := &MValue{Ptr: cMeta.ptr, Type: uint8(cMeta.Type)}
	val, err := decodeReflect(cMeta)
	if err != nil {
		return nil, err
	}

	return val.Interface(), nil
}

//export altCallFunction
func altCallFunction(id C.ulonglong, cMValueArgs C.struct_array) C.struct_array {
	exportedFunc := mValueFunctions[uint64(id)]
	funcType := exportedFunc.Type()

	args, err := decodeArgsExpensive(funcType, cMValueArgs)
	if err != nil {
		LogError("failed to call exported function:", err.Error())
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	if len(args) != funcType.NumIn() {
		LogError(fmt.Sprintf("failed to call exported function: argument count mismatch (required: %v, got: %v) - dont pass nil / none values", funcType.NumIn(), len(args)))
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
		LogError("exported function returned invalid value:", err.Error())
		return C.struct_array{array: nil, size: C.ulonglong(0)}
	}

	return cBytes
}
