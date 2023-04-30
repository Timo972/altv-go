package altv

// #include "capi.h"
import "C"
import (
	"errors"
	"fmt"
	"sync"
	"unsafe"
)

var baseObjectCache = sync.Map{}
var factories = sync.Map{}
var ErrNoFactory = errors.New("no factory found")
var ErrInvalidFactory = errors.New("invalid factory")

func getEntityData(e C.struct_entity) (typ BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) {
	ptr = unsafe.Pointer(e.ptr)
	id = uint32(e.id)
	typ = BaseObjectType(e.typ)
	model = uint32(e.model)

	return
}

func getOrCreateBaseObject[Type BaseObject](typ BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) (object Type, err error) {
	b, ok := baseObjectCache.Load(id)
	if !ok {
		f, ok := factories.Load(typ)
		if !ok {
			return object, ErrNoFactory
		}

		if typ == BaseTypeVehicle {
			factory, ok := f.(VehicleFactory)
			if !ok {
				return object, ErrInvalidFactory
			}

			object = factory(ptr, id, model).(Type)
			baseObjectCache.Store(id, object)
			return object, nil
		}

		factory, ok := f.(BaseFactory[Type])
		if !ok {
			return object, ErrInvalidFactory
		}

		object = factory(ptr, id)
		baseObjectCache.Store(id, object)
		return object, nil
	}

	fmt.Printf("loaded baseObject typ %v id %v from cache\n", typ, id)

	return b.(Type), nil
}

type BaseFactory[Type BaseObject] func(ptr unsafe.Pointer, id uint32) Type
type PlayerFactory BaseFactory[Player]
type VehicleFactory func(ptr unsafe.Pointer, id uint32, model uint32) Vehicle

// SetPlayerFactory sets the factory used by the package to create player struct instances
func SetPlayerFactory(factory PlayerFactory) {
	factories.Store(BaseTypePlayer, factory)
}

func SetVehicleFactory(factory VehicleFactory) {
	factories.Store(BaseTypeVehicle, factory)
}

func init() {
	SetPlayerFactory(NewPlayer)
	SetVehicleFactory(NewVehicle)
}

// getBaseObject ! internal only !
func getBaseObject[Type BaseObject](p C.struct_entity) (Type, error) {
	typ, ptr, id, model := getEntityData(p)

	return getOrCreateBaseObject[Type](typ, ptr, id, model)
}

// GetBaseObject ! internal only !
func GetBaseObject[Type BaseObject](typ BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) (Type, error) {
	return getOrCreateBaseObject[Type](typ, ptr, id, model)
}
