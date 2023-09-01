package resource

// #cgo CFLAGS: -I../internal/c-api/lib
// #cgo linux LDFLAGS: -L../internal/c-api/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/c-api/lib/win32 -lcapi -ldl -g
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

type PublicResource struct {
	ptr unsafe.Pointer
}

type LocalResource struct {
	PublicResource
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

// CurrentResource is the resource you are scripting in.
var Current *LocalResource

// ResourceByName returns a resource by it's name.
func ByName(name string) Resource {
	str := C.CString(name)
	defer C.free(unsafe.Pointer(str))

	ptr := C.core_get_resource_by_name(str)

	return &PublicResource{
		ptr: ptr,
	}
}

// AllResources returns all resources.
func All() []Resource {
	arr := C.core_get_all_resources()

	return cutil.NewArrayFunc[unsafe.Pointer, Resource](unsafe.Pointer(arr.ptr), int(arr.size), func(item unsafe.Pointer) Resource {
		return &PublicResource{
			ptr: item,
		}
	})
}

func (r PublicResource) IsStarted() bool {
	return uint8(C.resource_is_started(r.ptr)) == 1
}

func (r LocalResource) IsStarted() bool {
	return true
}

func (r PublicResource) Type() string {
	return C.GoString(C.resource_get_type(r.ptr))
}

func (r LocalResource) Type() string {
	return "go"
}

func (r PublicResource) Name() string {
	return C.GoString(C.resource_get_name(r.ptr))
}

func (r LocalResource) Name() string {
	return r.name
}

func (r PublicResource) Main() string {
	return C.GoString(C.resource_get_main(r.ptr))
}

func (r PublicResource) Dependencies() []string {
	cDeps := C.resource_get_dependencies(r.ptr)

	return cutil.NewStringArray(unsafe.Pointer(cDeps.ptr), int(cDeps.size))
}

func (r PublicResource) Dependants() []string {
	cDeps := C.resource_get_dependants(r.ptr)

	return cutil.NewStringArray(unsafe.Pointer(cDeps.ptr), int(cDeps.size))
}

func (r PublicResource) RequiredPermissions() []perm.Permission {
	data := C.resource_get_required_permissions(r.ptr)
	return newPermissionArray(data)
}

func (r PublicResource) OptionalPermissions() []perm.Permission {
	data := C.resource_get_optional_permissions(r.ptr)
	return newPermissionArray(data)
}

func (r PublicResource) Path() string {
	return C.GoString(C.resource_get_path(r.ptr))
}

func (r LocalResource) Path() string {
	return r.path
}

func (r PublicResource) Config(out any) error {
	return nil
}

/*func (r PublicResource) Import(name string, out any) error {
	return imprt.New(r.Name(), name, out)
}*/
