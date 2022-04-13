package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"errors"
	"fmt"
	"reflect"
	"unsafe"
)

func getExortName(t reflect.StructField) string {
	var name string

	name, ok := t.Tag.Lookup("alt")
	if !ok {
		name = t.Name
	}

	return name
}

// Export exports a struct
func Export(export interface{}) (err error) {
	cResource := C.CString(Resource.Name)
	defer C.free(unsafe.Pointer(cResource))

	rv := reflect.ValueOf(export)
	rt := reflect.TypeOf(export)

	if rt.Kind() != reflect.Struct {
		return errors.New("export must be a struct")
	}

	// export data
	for i := 0; i < rv.NumField(); i++ {
		field := rv.Field(i)
		fieldType := rt.Field(i)

		exportName := getExortName(fieldType)
		cExportName := C.CString(exportName)
		//defer C.free(unsafe.Pointer(cExportName)) not freeing it because module needs it while whole runtime

		mValue := CreateMValue(field.Interface())

		exported := int(C.register_alt_export(cResource, cExportName, C.struct_data{mValue: mValue.Ptr, Type: C.uint(mValue.Type)})) == 1
		if !exported {
			err = fmt.Errorf("failed to export %s", exportName)
		}
	}

	// export methods
	for i := 0; i < rv.NumMethod(); i++ {
		method := rt.Method(i)
		// this enabled means you can not export methods in camelCase - only PascalCase
		// if !method.IsExported() {
		// 	continue
		// }

		exportName := method.Type.Name()
		cExportName := C.CString(exportName)

		mValue := CreateMValue(method.Func.Interface())

		exported := int(C.register_alt_export(cResource, cExportName, C.struct_data{mValue: mValue.Ptr, Type: C.uint(mValue.Type)})) == 1
		if !exported {
			err = fmt.Errorf("failed to export %s", exportName)
		}
	}

	return err
}

func Import[ValueType any](resource string, name string) (value ValueType, _ error) {
	cTargetResource := C.CString(resource)
	defer C.free(unsafe.Pointer(cTargetResource))
	cExport := C.CString(name)
	defer C.free(unsafe.Pointer(cExport))

	cMetaData := C.get_alt_export(cTargetResource, cExport)
	if cMetaData.Ptr == nil {
		return value, fmt.Errorf("failed to get export '%s' of resource '%s'; Make sure you set dependencies correctly", name, resource)
	}

	mVal := &MValue{Ptr: cMetaData.Ptr, Type: uint8(cMetaData.Type)}

	ok := mVal.GetValue(&value)
	if !ok {
		return value, errors.New("invalid mvalue")
	}

	return value, nil
}

type ChatRegisterCmd = func(cmd string, description string, callback func(player *Player, args ...[]string))

func test() {
	registerCmd, err := Import[ChatRegisterCmd]("chat", "registerCmd")
	if err != nil {
		panic(err)
	}
	registerCmd("/test", "", func(p *Player, args ...[]string) {
		LogInfo("test")
	})
}
