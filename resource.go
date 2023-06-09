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
	RequiredPermissions() []Permission
	// OptionalPermissions returns the optional permissions the player can grant for this resource.
	OptionalPermissions() []Permission
	// Path returns the resource path.
	Path() string
	// Config populates the given struct with the resource config.
	Config(out any) error
	// Import imports a value exported by another resource, no matter which language. See mvalue serialization for more information about supported values.
	Import(name string, out any) error
}

// CurrentResource is the resource you are scripting in.
var CurrentResource Resource

// ResourceByName returns a resource by it's name.
func ResourceByName(name string) Resource {
	str := C.CString(name)
	defer C.free(unsafe.Pointer(str))

	ptr := C.core_get_resource_by_name(str)

	return &publicResource{
		ptr: ptr,
	}
}

// AllResources returns all resources.
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

func (r publicResource) Exports(out any) error {
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

func (r publicResource) Config(out any) error {
	return nil
}

func (r publicResource) Import(name string, out any) error {
	return resourceImport(r.Name(), name, out)
}
