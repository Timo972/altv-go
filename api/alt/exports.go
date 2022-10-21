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

func registerExport(cResource *C.char, exportName string, field reflect.Value) error {
	pv, err := encode(field.Interface())
	if err != nil {
		return err
	}

	cExportName := C.CString(exportName)
	defer C.free(unsafe.Pointer(cExportName)) // not freeing it because module needs it while whole runtime

	exp := int(C.runtime_register_alt_export(cResource, cExportName, (*C.uchar)(pv.array), pv.size)) == 1
	if !exp {
		return fmt.Errorf("failed to register export '%s'", exportName)
	}
	return nil
}

// Export exports a struct
func Export(export interface{}) error {
	cResource := C.CString(CurrentResource.Name())
	defer C.free(unsafe.Pointer(cResource))

	rv := reflect.ValueOf(export)
	rt := reflect.Type()
	Of(export)

	if rt.Kind() != reflect.Struct {
		return errors.New("export must be a struct")
	}

	// export data
	for i := 0; i < rv.NumField(); i++ {
		field := rv.Field(i)
		fieldType := rt.Field(i)
		exportName := getFieldName(fieldType)

		registerExport(cResource, exportName, field)
	}

	// export methods
	for i := 0; i < rv.NumMethod(); i++ {
		method := rt.Method(i)
		// this enabled means you can not export methods in camelCase - only PascalCase
		// if !method.IsExported() {
		// 	continue
		// }
		exportName := method.Type().Name()

		registerExport(cResource, exportName, method.Func)
	}

	return nil
}

func Import[ValueType any](resource string, name string) (value ValueType, _ error) {
	cTargetResource := C.CString(resource)
	defer C.free(unsafe.Pointer(cTargetResource))
	cExport := C.CString(name)
	defer C.free(unsafe.Pointer(cExport))

	cProtoArray := C.runtime_get_alt_export(cTargetResource, cExport)
	imp, err := decodeReflect(cProtoArray)
	if err != nil {
		return *new(ValueType), err
	}

	value, ok := imp.Interface().(ValueType)
	if !ok {
		return *new(ValueType), errors.New("export is not of type specified type")
	}
	//if cMetaData.ptr == nil {
	//	return value, fmt.Errorf("failed to get export '%s' of resource '%s'; Make sure you set dependencies correctly", name, resource)
	//}

	return value, nil
}
