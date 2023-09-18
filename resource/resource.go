package resource

// #cgo CFLAGS: -I../internal/capi/lib
// #cgo linux LDFLAGS: -L../internal/capi/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/capi/lib/win32 -lcapi -ldl -g
// #cgo darwin LDFLAGS: -L../internal/capi/lib/darwin -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"
import (
	"unsafe"

	"github.com/timo972/altv-go/internal/cutil"
	"github.com/timo972/altv-go/perm"
)

func newPermissionArray(arr C.struct_array) []perm.Permission {
	return cutil.NewArrayFunc[C.uchar, perm.Permission](unsafe.Pointer(arr.ptr), int(arr.size), func(item C.uchar) perm.Permission {
		return perm.Permission(item)
	})
}

type Public struct {
	ptr unsafe.Pointer
}

type Local struct {
	Public
	name string
	path string
}

type Resource interface {
	// IsStarted returns true if the resource is started.
	IsStarted() bool
	// Type returns the resource type. e.g. js, jsv2, cs, go, ...
	Type() string
	// Name returns the resource name.
	Name() string
	// Main returns the resource main file.
	Main() string
	// Exports populates the given struct with the resource exports.
	// Exports(out any) error
	// Dependencies returns resource names the resource depends on.
	Dependencies() []string
	// Dependants returns resource names that depend on this resource.
	Dependants() []string
	// RequiredPermissions returns the required permissions the player has to grant for this resource.
	RequiredPermissions() []perm.Permission
	// OptionalPermissions returns the optional permissions the player can grant for this resource.
	OptionalPermissions() []perm.Permission
	// Path returns the resource path.
	Path() string
	// Config populates the given struct with the resource config.
	Config(out any) error
	// Import imports a value exported by another resource, no matter which language. See mvalue serialization for more information about supported values.
	// Import(name string, out any) error
}

// ResourceByName returns a resource by it's name.
func ByName(name string) Resource {
	str := C.CString(name)
	defer C.free(unsafe.Pointer(str))

	ptr := C.core_get_resource_by_name(str)

	return &Public{
		ptr: ptr,
	}
}

// AllResources returns all resources.
func All() []Resource {
	arr := C.core_get_all_resources()

	return cutil.NewArrayFunc[unsafe.Pointer, Resource](unsafe.Pointer(arr.ptr), int(arr.size), func(item unsafe.Pointer) Resource {
		return &Public{
			ptr: item,
		}
	})
}

func (r Public) IsStarted() bool {
	return uint8(C.resource_is_started(r.ptr)) == 1
}

func (r Local) IsStarted() bool {
	return true
}

func (r Public) Type() string {
	return C.GoString(C.resource_get_type(r.ptr))
}

func (r Local) Type() string {
	return "go"
}

func (r Public) Name() string {
	return C.GoString(C.resource_get_name(r.ptr))
}

func (r Local) Name() string {
	return r.name
}

func (r Public) Main() string {
	return C.GoString(C.resource_get_main(r.ptr))
}

func (r Public) Dependencies() []string {
	cDeps := C.resource_get_dependencies(r.ptr)

	return cutil.NewStringArray(unsafe.Pointer(cDeps.ptr), int(cDeps.size))
}

func (r Public) Dependants() []string {
	cDeps := C.resource_get_dependants(r.ptr)

	return cutil.NewStringArray(unsafe.Pointer(cDeps.ptr), int(cDeps.size))
}

func (r Public) RequiredPermissions() []perm.Permission {
	data := C.resource_get_required_permissions(r.ptr)
	return newPermissionArray(data)
}

func (r Public) OptionalPermissions() []perm.Permission {
	data := C.resource_get_optional_permissions(r.ptr)
	return newPermissionArray(data)
}

func (r Public) Path() string {
	return C.GoString(C.resource_get_path(r.ptr))
}

func (r Local) Path() string {
	return r.path
}

func (r Public) Config(out any) error {
	return nil
}

/*func (r Public) Import(name string, out any) error {
	return imprt.New(r.Name(), name, out)
}*/
