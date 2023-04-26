package altv

// #include "capi.h"
import "C"
import (
	"errors"
	"sync"
	"unsafe"
)

var baseObjectCache = sync.Map{}
var factories = sync.Map{}
var ErrNoFactory = errors.New("no factory found")
var ErrInvalidFactory = errors.New("invalid factory")

func getEntityData(e C.struct_entity) (ptr unsafe.Pointer, id uint32, typ BaseObjectType) {
	ptr = unsafe.Pointer(e.ptr)
	id = uint32(e.id)
	typ = altv.BaseObjectType(e.typ)

	return
}

func getOrCreateBaseObject[Type Player](ptr unsafe.Pointer, id uint32, typ BaseObjectType) (Type, error) {
	b, ok := baseObjectCache.Load(id)
	if !ok {
		f, ok := factories.Load(typ)
		if !ok {
			return nil, ErrNoFactory
		}

		factory, ok := f.(BaseFactory[Type])
		if !ok {
			return nil, ErrInvalidFactory
		}

		return factory(ptr, id), nil
	}

	return b.(Type), nil
}

type BaseFactory[Type BaseObject] = func(ptr unsafe.Pointer, id uint32) Type
type PlayerFactory = BaseFactory[Player]

// SetPlayerFactory sets the factory used by the package to create player struct instances
func SetPlayerFactory(factory PlayerFactory) {
	factories.Store(BaseTypePlayer, factory)
}

func init() {
	SetPlayerFactory(NewPlayer)
}

// GetBaseObject ! internal only ! 
func GetBaseObject[Type BaseObject](p C.struct_entity) (Type, error) {
	ptr, id, typ := getEntityData(p)

	return getOrCreateBaseObject[Type](ptr, id, typ)
}
