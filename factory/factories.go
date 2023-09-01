package factory

// #cgo CFLAGS: -I../internal/c-api/lib
// #cgo linux LDFLAGS: -L../internal/c-api/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/c-api/lib/win32 -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"
import (
	"errors"
	"fmt"
	"sync"
	"unsafe"

	"github.com/timo972/altv-go/altlog"
	"github.com/timo972/altv-go/entity"
)

var baseObjectCache = sync.Map{}
var factories = sync.Map{}
var ErrNoFactory = errors.New("no factory found")
var ErrInvalidFactory = errors.New("invalid factory")

func getOrCreateBaseObject[Type entity.BaseObject](typ entity.BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) (object Type, err error) {
	b, ok := baseObjectCache.Load(id)
	if !ok {
		f, ok := factories.Load(typ)
		if !ok {
			return object, ErrNoFactory
		}

		if typ == entity.TypeVehicle {
			factory, ok := f.(VehicleFactory)
			if !ok {
				return object, ErrInvalidFactory
			}

			object = factory(ptr, id, model).(Type)
			baseObjectCache.Store(id, object)
			return object, nil
		}

		if typ == entity.TypePlayer {
			factory, ok := f.(BaseFactory[entity.Player])
			if !ok {
				return object, ErrInvalidFactory
			}

			object = factory(ptr, id).(Type)
			baseObjectCache.Store(id, object)
			return object, nil
		}

		factory, ok := f.(BaseFactory[Type])
		if !ok {
			fmt.Printf("factory is not BaseFactory[Type]: %T != %T\n", factory, f)
			return object, ErrInvalidFactory
		}

		object = factory(ptr, id)
		baseObjectCache.Store(id, object)
		return object, nil
	}

	fmt.Printf("loaded baseObject typ %v id %v from cache\n", typ, id)

	return b.(Type), nil
}

type BaseFactory[Type entity.BaseObject] func(ptr unsafe.Pointer, id uint32) Type
type VehicleFactory func(ptr unsafe.Pointer, id uint32, model uint32) entity.Vehicle

// SetPlayerFactory sets the factory used by the package to create player struct instances
func SetPlayerFactory(factory BaseFactory[entity.Player]) {
	factories.Store(entity.TypePlayer, factory)
	fmt.Println("Player Factory loaded", entity.TypePlayer, factory)
}

func SetVehicleFactory(factory VehicleFactory) {
	factories.Store(entity.TypeVehicle, factory)
	fmt.Println("Vehicle Factory loaded", entity.TypeVehicle, factory)
}

func init() {
	SetPlayerFactory(entity.NewPlayer)
	SetVehicleFactory(entity.NewVehicle)
}

// GetBaseObject ! internal only !
func GetBaseObject[Type entity.BaseObject](typ entity.BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) (Type, error) {
	return getOrCreateBaseObject[Type](typ, ptr, id, model)
}

//export altCreateBaseObject
func altCreateBaseObject(e *C.struct_baseObject) {
	fmt.Printf("altCreateBaseObject\n")
	id := uint32(e.id)
	typ := entity.BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)
	model := uint32(e.model)

	if _, err := GetBaseObject[entity.BaseObject](typ, ptr, id, model); err != nil {
		altlog.Errorln(fmt.Sprintf("altCreateBaseObject: %s", err.Error()))
	}
}

//export altRemoveBaseObject
func altRemoveBaseObject(e *C.struct_baseObject) {
	fmt.Printf("altRemoveBaseObject\n")
	id := uint32(e.id)
	typ := entity.BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)
	model := uint32(e.model)

	obj, err := GetBaseObject[entity.BaseObject](typ, ptr, id, model)
	if err != nil {
		altlog.Errorln(fmt.Sprintf("altRemoveBaseObject: %s", err.Error()))
		return
	}

	obj.CancelCtx(entity.ErrInvalidBaseObject)
	baseObjectCache.Delete(id)
}
