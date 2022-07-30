package alt

import "unsafe"

type IBaseObjectPool[TBaseObject IBaseObject] interface {
	Create(ptr unsafe.Pointer) TBaseObject
	Remove(entity TBaseObject)
	Get(ptr unsafe.Pointer) TBaseObject
	GetOrCreate(ptr unsafe.Pointer) TBaseObject
	AllBaseObjects() []TBaseObject
}

type BaseObjectPool[TBaseObject IBaseObject] struct {
	entities map[unsafe.Pointer]TBaseObject
	factory  BaseObjectFactory
}

func (b *BaseObjectPool[TBaseObject]) Create(ptr unsafe.Pointer, t BaseObjectType) TBaseObject {
	if ptr == nil {
		// TODO: return default?
		return nil
	}

	if e, ok := b.entities[ptr]; ok {
		// baseObject already exists
		return e
	}
	var e TBaseObject
	e = &BaseObject{}
	e = b.factory.Create(ptr, t)
	b.Add(e)
	return e
}

func (b *BaseObjectPool[TBaseObject]) Add(entity TBaseObject) {
	b.entities[entity.nativePtr()] = entity
}
