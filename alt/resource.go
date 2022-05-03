package alt

// #cgo windows CFLAGS: -I../c-api/lib/win32
// #cgo windows LDFLAGS: -L../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../c-api/lib/linux
// #cgo linux LDFLAGS: -L../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"log"
	"unsafe"
)

/*type resource struct {
	Ptr  unsafe.Pointer
	Name string
	Path string
}*/

type publicResource struct {
	ptr unsafe.Pointer
	/*IsStarted           bool
	Type                string
	Name                string
	Main                string
	Exports             map[string]interface{}
	Dependencies        []string
	Dependants          []string
	RequiredPermissions []Permission
	OptionalPermissions []Permission

	Path   string
	Config map[string]interface{}*/
}

type localResource struct {
	publicResource
	name string
	path string
}

type IResource interface {
	IsStarted() bool
	Type() string
	Name() string
	Main() string
	Exports(out interface{}) error
	ExportsInterface() (interface{}, error)
	Dependencies() []string
	Dependants() []string
	RequiredPermissions() []Permission
	OptionalPermissions() []Permission
	Path() string
	Config(out interface{}) error
	ConfigInterface() (interface{}, error)
}

var CurrentResource IResource

//export initGoResource
func initGoResource(ptr unsafe.Pointer, name *C.char, path *C.char) {
	CurrentResource = &localResource{
		name: C.GoString(name),
		path: C.GoString(path),
		publicResource: publicResource{
			ptr: ptr,
		},
	}

	cstr := C.CString("go-module")
	defer C.free(unsafe.Pointer(cstr))

	log.SetFlags(log.Ltime)

	moduleLoaded := int(C.load_module(cstr))
	if moduleLoaded == 0 {
		log.Fatal("Couldn't locate go-module library.")
	}
}

func ResourceByName(name string) IResource {
	str := C.CString(name)
	defer C.free(unsafe.Pointer(str))

	ptr := C.core_get_resource_by_name(str)

	return &publicResource{
		ptr: ptr,
	}
}

func AllResources() []IResource {
	arr := C.core_get_all_resources()
	size := int(arr.size)
	ptrs := (*[1 << 28]unsafe.Pointer)(arr.array)[:size:size]

	resources := make([]IResource, size)

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
	data := C.resource_get_exports(r.ptr)

	return decode(data, out)
}

func (r publicResource) ExportsInterface() (interface{}, error) {
	data := C.resource_get_exports(r.ptr)

	return decodeReflect(data)
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
	data := C.resource_get_config(r.ptr)
	return decode(data, out)
}

func (r publicResource) ConfigInterface() (interface{}, error) {
	data := C.resource_get_config(r.ptr)
	return decodeReflect(data)
}
