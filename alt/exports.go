package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"unsafe"
)

func Export(name string, export interface{}) bool {
	mValue := CreateMValue(export)

	cResource := C.CString(Resource.Name)
	defer C.free(unsafe.Pointer(cResource))
	cExport := C.CString(name)
	//defer C.free(unsafe.Pointer(cExport)) not freeing it because module needs it while whole runtime

	exported := int(C.register_alt_export(cResource, cExport, C.struct_data{mValue: mValue.Ptr, Type: C.uint(mValue.Type)})) == 1
	return exported
}

func Import[ValueType any](resource string, name string) ValueType {
	cTargetResource := C.CString(resource)
	defer C.free(unsafe.Pointer(cTargetResource))
	cExport := C.CString(name)
	defer C.free(unsafe.Pointer(cExport))

	cMetaData := C.get_alt_export(cTargetResource, cExport)
	mVal := &MValue{Ptr: cMetaData.Ptr, Type: uint8(cMetaData.Type)}

	value := mVal.GetValue()

	return value.(ValueType)
}
