package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"
import (
	"unsafe"
)

type publicResource struct {
	ptr unsafe.Pointer
}

type localResource struct {
	publicResource
	name string
	path string
}

type Resource interface {
	IsStarted() bool
	Type() string
	Name() string
	Main() string
	Exports(out interface{}) error
	Dependencies() []string
	Dependants() []string
	RequiredPermissions() []Permission
	OptionalPermissions() []Permission
	Path() string
	Config(out interface{}) error
}

var CurrentResource Resource

func ResourceByName(name string) Resource {
	str := C.CString(name)
	defer C.free(unsafe.Pointer(str))

	ptr := C.core_get_resource_by_name(str)

	return &publicResource{
		ptr: ptr,
	}
}

func AllResources() []Resource {
	arr := C.core_get_all_resources()
	size := int(arr.size)
	ptrs := (*[1 << 28]unsafe.Pointer)(arr.array)[:size:size]

	resources := make([]Resource, size)

	for i, ptr := range ptrs {
		resources[i] = &publicResource{ptr: ptr}
	}

	return resources
}

func (r publicResource) IsStarted() bool {
	return uint8(C.resource_is_started(r.ptr)) == 1
}

func (r localResource) IsStarted() bool {
	return true
}

func (r publicResource) Type() string {
	return C.GoString(C.resource_get_type(r.ptr))
}

func (r localResource) Type() string {
	return "go"
}

func (r publicResource) Name() string {
	return C.GoString(C.resource_get_name(r.ptr))
}

func (r localResource) Name() string {
	return r.name
}

func (r publicResource) Main() string {
	return C.GoString(C.resource_get_main(r.ptr))
}

func (r publicResource) Exports(out interface{}) error {
	return nil
}

func (r publicResource) Dependencies() []string {
	cDeps := C.resource_get_dependencies(r.ptr)

	return newStringArray(unsafe.Pointer(cDeps.array), int(cDeps.size))
}

func (r publicResource) Dependants() []string {
	cDeps := C.resource_get_dependants(r.ptr)

	return newStringArray(unsafe.Pointer(cDeps.array), int(cDeps.size))
}

func (r publicResource) RequiredPermissions() []Permission {
	data := C.resource_get_required_permissions(r.ptr)
	return newPermissionArray(data)
}

func (r publicResource) OptionalPermissions() []Permission {
	data := C.resource_get_optional_permissions(r.ptr)
	return newPermissionArray(data)
}

func (r publicResource) Path() string {
	return C.GoString(C.resource_get_path(r.ptr))
}

func (r localResource) Path() string {
	return r.path
}

func (r publicResource) Config(out interface{}) error {
	return nil
}
